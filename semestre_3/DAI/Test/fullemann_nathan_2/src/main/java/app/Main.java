package app;

import io.javalin.Javalin;
import com.fasterxml.jackson.databind.ObjectMapper;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        // Initialisation de Javalin
        Javalin app = Javalin.create().start(7000);

        // Articles disponibles
        List<Map<String, Object>> articles = new ArrayList<>(List.of(
                Map.of("id", 1, "name", "PS5", "price", 300.0),
                Map.of("id", 2, "name", "FIFA 24", "price", 75.0)
        ));

        // ObjectMapper pour traiter le JSON
        ObjectMapper objectMapper = new ObjectMapper();

        // Récupérer le panier à partir d'un cookie (ou en créer un nouveau)
        Cart getCartFromCookie(io.javalin.http.Context ctx) {
            try {
                String cookieString = ctx.cookie("cart");
                if (cookieString != null) {
                    return new Cart(cookieString);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            return new Cart();
        }

        // Sauvegarder le panier dans un cookie
        void saveCartToCookie(io.javalin.http.Context ctx, Cart cart) {
            try {
                String cookieString = cart.toCookie();
                ctx.cookie("cart", cookieString);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        // GET /api/articles - Liste des articles
        app.get("/api/articles", ctx -> {
            ctx.json(articles);
        });

        // GET /api/articles/{id} - Récupérer un article par ID
        app.get("/api/articles/{id}", ctx -> {
            int id = Integer.parseInt(ctx.pathParam("id"));
            Map<String, Object> article = articles.stream()
                    .filter(a -> a.get("id").equals(id))
                    .findFirst()
                    .orElse(null);

            if (article != null) {
                ctx.json(article);
            } else {
                ctx.status(404).result("Article not found");
            }
        });

        // POST /api/cart - Ajouter ou mettre à jour un article dans le panier
        app.post("/api/cart", ctx -> {
            // Récupérer le panier depuis le cookie
            Cart cart = getCartFromCookie(ctx);

            // Lecture des données de la requête
            Map<String, Integer> body = objectMapper.readValue(ctx.body(), Map.class);
            int articleId = body.get("articleId");
            int quantity = body.get("quantity");

            // Vérifier si l'article existe
            boolean articleExists = articles.stream().anyMatch(a -> a.get("id").equals(articleId));
            if (!articleExists) {
                ctx.status(404).result("Article not found");
                return;
            }

            // Ajouter ou mettre à jour l'article dans le panier
            cart.put(articleId, quantity);

            // Sauvegarder le panier dans un cookie
            saveCartToCookie(ctx, cart);
            ctx.result("Article added/updated in cart");
        });

        // GET /api/cart - Liste des articles dans le panier
        app.get("/api/cart", ctx -> {
            // Récupérer le panier depuis le cookie
            Cart cart = getCartFromCookie(ctx);

            List<Map<String, Object>> cartDetails = new ArrayList<>();

            for (Map.Entry<Integer, Integer> entry : cart.entrySet()) {
                int articleId = entry.getKey();
                int quantity = entry.getValue();

                // Récupérer les détails de l'article
                Map<String, Object> article = articles.stream()
                        .filter(a -> a.get("id").equals(articleId))
                        .findFirst()
                        .orElse(null);

                if (article != null) {
                    Map<String, Object> cartItem = new HashMap<>(article);
                    cartItem.put("quantity", quantity);
                    cartDetails.add(cartItem);
                }
            }

            ctx.json(cartDetails);
        });

        // DELETE /api/cart/{id} - Retirer un article du panier
        app.delete("/api/cart/{id}", ctx -> {
            // Récupérer le panier depuis le cookie
            Cart cart = getCartFromCookie(ctx);

            int articleId = Integer.parseInt(ctx.pathParam("id"));

            if (cart.containsKey(articleId)) {
                cart.remove(articleId);

                // Sauvegarder le panier mis à jour dans un cookie
                saveCartToCookie(ctx, cart);
                ctx.result("Article removed from cart");
            } else {
                ctx.status(404).result("Article not in cart");
            }
        });

        // POST /api/purchase - Effectuer un achat et vider le panier
        app.post("/api/purchase", ctx -> {
            // Récupérer le panier depuis le cookie
            Cart cart = getCartFromCookie(ctx);

            if (cart.isEmpty()) {
                ctx.status(400).result("Cart is empty, nothing to purchase");
            } else {
                cart.clear();

                // Vider le panier dans le cookie
                saveCartToCookie(ctx, cart);
                ctx.result("Purchase successful. Cart emptied.");
            }
        });
    }
}