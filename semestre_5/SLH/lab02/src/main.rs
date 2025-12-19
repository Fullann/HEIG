#![doc = include_str!("../README.md")]

use std::path::Path;
use rocket::fs::FileServer;

use reqwest::{
    Url,
    header::{HeaderMap, HeaderValue},
};
use rocket::{
    FromForm, Request, State, catch, catchers,
    form::Form,
    fs::TempFile,
    get,
    http::{Cookie, CookieJar, SameSite},
    main, post,
    response::Redirect,
    routes,
    serde::json::Json,
};
use rocket_dyn_templates::{Template, context};
use rocket_oauth2::{OAuth2, TokenResponse};
use serde::Deserialize;

pub use crate::auth::{ConnectedAdministrator, ConnectedUser};
use crate::database::user;

mod auth;
mod database;

struct GitHub;

// This route calls `get_redirect`, which sets up a token request and
// returns a `Redirect` to the authorization endpoint.
#[get("/login/github")]
fn github_login(oauth2: OAuth2<GitHub>, cookies: &CookieJar<'_>) -> Redirect {
    // Request the "read:user" scope to get profile info
    oauth2.get_redirect(cookies, &["read:user"]).unwrap() 
}

// This route, mounted at the application's Redirect URI, uses the
// `TokenResponse` request guard to complete the token exchange and obtain
// the token.
#[get("/auth/github")]
async fn github_callback(
    token: TokenResponse<GitHub>,
    cookies: &CookieJar<'_>,
    users: &State<user::Db>,
) -> Option<Redirect> {
    let access_token = token.access_token();

    #[derive(Debug, Deserialize)]
    struct GitHubUser {
        id: u64,
        login: String,
        avatar_url: Option<Url>,
        name: Option<String>,
    }

    let mut headers = HeaderMap::new();
    headers.insert("User-Agent", HeaderValue::from_static("HEIG-VD SLH Lab02"));
    headers.insert(
        "Authorization",
        HeaderValue::from_str(&format!("Bearer {access_token}")).ok()?,
    );
    headers.insert(
        "Accept",
        HeaderValue::from_static("application/vnd.github+json"),
    );

    let gh_user: GitHubUser = reqwest::Client::builder()
        .default_headers(headers)
        .build()
        .ok()?
        .get("https://api.github.com/user")
        .send()
        .await
        .ok()?
        .json()
        .await
        .ok()?;

    let user = user::UserDb {
        id: gh_user.id,
        login: gh_user.login,
        avatar: gh_user.avatar_url,
        name: gh_user.name,
        liked_posts: Vec::new(),
    };
    let user_id = user.id;

    users.insert_user(user).ok()?;

    // Set a private cookie with the user id
    //
    // (private cookie are encrypted using authenticated encryption and key setted in Rocket
    // config)
    cookies.add_private(Cookie::new("user_id", user_id.to_string()));

    Some(Redirect::to("/"))
}

#[get("/")]
async fn index(user: Option<ConnectedUser>, posts: &State<database::post::Db>) -> Template {
    let len_posts = posts.read().expect("Poisoned DB").len();
    Template::render("index", context! {len_posts: len_posts, user})
}

#[get("/login")]
fn login() -> Template {
    Template::render("login", context! {title: "Mon titre"})
}
#[get("/logout")]
fn logout(cookies: &CookieJar<'_>) -> Redirect {
    cookies.remove_private(Cookie::from("user_id"));
    Redirect::to("/")
}
#[get("/create")]
fn create_post(user: ConnectedUser) -> Template {
    Template::render("create_post", context! {title: "Mon titre", user})
}

#[get("/reset")]
fn reset_db(
    user: ConnectedAdministrator,
    users: &State<user::Db>,
    posts: &State<database::post::Db>,
) -> Redirect {
    users.clear(&user).ok(); 
    posts.clear(&user).ok();
    Redirect::to("/")
}
#[get("/home")]
fn home(
    user: ConnectedUser,
    users: &State<user::Db>,
    posts: &State<database::post::Db>,
) -> Template {
    let posts = posts.read().expect("Poisoned DB");
    let users = users.read().expect("Poisoned DB");
    let posts: Vec<_> = posts.values().collect();
    let users: Vec<_> = users.values().collect();
    Template::render("home", context! {title: "Mon titre", user, posts, users})
}

#[catch(401)]
fn not_authorized(_req: &Request) -> Template {
    Template::render(
        "login",
        context! {error_message: "401 Unauthorized: The request requires user authentication."},
    )
}
#[catch(404)]
fn not_found(_req: &Request) -> Template {
    Template::render(
        "home",
        context! {error_message: "404 Not Found: The requested resource could not be found."},
    )
}

#[derive(FromForm)]
struct CreateForm<'r> {
    text: &'r str,
    file: Option<TempFile<'r>>,
}

#[post("/post/create", data = "<data>")]
async fn perform_create_port(
    user: ConnectedUser, // Filled todo type
    data: Form<CreateForm<'_>>,
    posts: &State<database::post::Db>,
) -> Option<Redirect> {
    let CreateForm { text, file } = data.into_inner();
    
    let path = if let Some(mut f) = file {
        // BONUS: Content Type Validation
        let content_type = f.content_type()?;
        if !content_type.is_jpeg() && !content_type.is_png() && !content_type.is_bmp() {
            eprintln!("Invalid file type: {:?}", content_type);
            return None; // Or handle error gracefully
        }

        // Logic to save file
        let path = Path::new("image");
        // Note: The actual saving to a specific ID path happens inside posts.create_post
        // But the TempFile needs to persist. 
        // In the original code provided, it copied to "tmp".
        // Let's keep it simple: pass the TempFile path if it persists, 
        // OR better yet, let the database logic handle the copy as it currently does.
        
        // However, `posts.create_post` expects a &Path. 
        // We need to persist the TempFile to disk briefly so database.rs can copy it.
        let tmp_path = Path::new("/tmp").join(f.name().unwrap_or("upload"));
        f.copy_to(&tmp_path).await.ok()?;
        Some(tmp_path)
    } else {
        None
    };

    posts
        .create_post(&user, text.to_string(), path.as_deref())
        .await
        .ok()?;
        
    Some(Redirect::to("/"))
}

#[derive(Deserialize, Clone, Copy)]
#[serde(rename_all = "lowercase")]
enum Action {
    Like,
    Dislike,
}
#[derive(Deserialize, Copy, Clone)]
struct PerformLike {
    post_id: u64,
    action: Action,
}

#[post("/post/like", data = "<data>")]
async fn perform_like(
    user: ConnectedUser,
    data: Json<PerformLike>,
    posts: &State<database::post::Db>,
) -> Option<&'static str> {
    match data.action {
        Action::Like => posts.add_like(&user, data.post_id).await.ok()?,
        Action::Dislike => posts.del_like(&user, data.post_id).await.ok()?,
    };
    Some("")
}

#[main]
async fn main() -> Result<(), eyre::Error> {
    let users = user::Db::load(Path::new("data/users.json"))?;
    let posts = database::post::Db::load(Path::new("data/posts.json"))?;

    let _rocket = rocket::build()
        .mount(
            "/",
            routes![
                index,
                login,
                logout,
                github_login,
                github_callback,
                create_post,
                perform_create_port,
                home,
                perform_like,
                reset_db
            ],
        )
        .mount("/image", FileServer::from("image")) 
        .register("/", catchers![not_authorized, not_found])
        .attach(Template::fairing())
        .attach(OAuth2::<GitHub>::fairing("github"))
        .manage(users)
        .manage(posts)
        .launch()
        .await?;

    Ok(())
}
