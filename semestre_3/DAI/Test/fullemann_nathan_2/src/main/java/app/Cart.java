package app;

import java.util.*;
import com.fasterxml.jackson.databind.ObjectMapper;

/**
 * Represents a shopping cart.
 * Extends HashMap<Integer, Integer> with an article ID as key and the quantity to purchase as value.
 *
 * The method cart.toCookie() returns a string that can be used as a cookie.
 * 
 * The constructor create a Cart object from a cookie string.
 */
class Cart extends HashMap<Integer, Integer> {
    ObjectMapper objectMapper = new ObjectMapper();

    public Cart() { }

    public Cart(String cookieString) throws Exception {
        String json = new String(Base64.getDecoder().decode(cookieString));
        var cart = objectMapper.readValue(json,  Cart.class);
        this.putAll(cart);
    }

    public String toCookie() throws Exception {
        String json = objectMapper.writeValueAsString(this);
        return Base64.getEncoder().encodeToString(json.getBytes());
    }
}
