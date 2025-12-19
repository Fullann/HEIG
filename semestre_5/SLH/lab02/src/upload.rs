use rocket::{
    form::Form,
    fs::TempFile,
    http::Status,
    response::Redirect,
    State,
};
use uuid::Uuid;

use crate::database::{ImagePost, Images};

#[derive(FromForm)]
pub struct Upload<'r> {
    pub description: String,
    pub file: TempFile<'r>,
}

#[post("/upload", data = "<form>")]
pub async fn upload_image(
    mut form: Form<Upload<'_>>,
    images: &State<Images>,
) -> Result<Redirect, Status> {
    let file = &mut form.file;

    // 5MB
    if file.len().unwrap_or(0) > 5 * 1024 * 1024 {
        return Err(Status::PayloadTooLarge);
    }

    let content_type = file.content_type().ok_or(Status::BadRequest)?;

    let extension = match content_type.as_str() {
        "image/png" => "png",
        "image/jpeg" => "jpg",
        _ => return Err(Status::UnsupportedMediaType),
    };

    let filename = format!("{}.{}", Uuid::new_v4(), extension);
    let path = format!("image/{}", filename);

    file.persist_to(&path).await.map_err(|_| Status::InternalServerError)?;

    images.add(ImagePost {
        owner: 0,
        filename,
        description: form.description.clone(),
    });

    Ok(Redirect::to("/"))
}
