# Lab04 - TLS et certificats
## Partie EMail
openssl req -new -config config.conf -out Fullemann-Email.csr -keyout Fullemann-Email.key

openssl req -new -config config.conf -out nathan.fullemann@heig-vd.ch.csr -keyout nathan.fullemann@heig-vd.ch.key

openssl ca -config config.conf -in ../mail_client/nathan.fullemann@heig-vd.ch.csr -out nathan.fullemann@heig-vd.ch.crt

cat nathan.fullemann@heig-vd.ch.crt ../mail_CA/Fullemann-Email.crt > CERTIF_CHAIN.crt

openssl pkcs12 -export -name enzo_p12 -inkey nathan.fullemann@heig-vd.ch.key -in nathan.fullemann@heig-vd.ch.crt -certfile ../CERTIF_CHAIN.crt -out nathan.fullemann@heig-vd.ch.p12


## Partie TLS

openssl req -new -config config.conf -out Fullemann-TLS.csr -keyout Fullemann-TLS.key

openssl req -new -config config.conf -out IP.csr -keyout IP.key

openssl ca -config config.conf -in ../TLS_client/IP.csr -out IP.crt

cat IP.crt ../TLS_CA/Fullemann-TLS.crt > CERTIF_CHAIN.crt

### Configuration nginx
````
#HTTPS REDIRECTION
#server {
#
#    listen 80 default_server;
#
#    server_name _;
#
#    return 301 https://$host$request_uri;
#}

server {

listen 443 ssl http2;
listen [::]:443 ssl http2;

ssl_certificate CERTIF_CHAIN.crt;
ssl_certificate_key IP.key;
ssl_session_timeout 1d;
ssl_session_cache shared:MozSSL:10m;  # about 40000 sessions
ssl_session_tickets off;

# intermediate configuration
ssl_protocols TLSv1.2 TLSv1.3;
# Keep only the ciphersuite recommended by https://ciphersuite.info/cs/
ssl_ciphers ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-ECDSA-CHACHA20-POLY1305;
ssl_prefer_server_ciphers on;

# HSTS (ngx_http_headers_module is required) (63072000 seconds)
add_header Strict-Transport-Security "max-age=63072000" always;

access_log /var/www/labo-crypto.com/logs/access.log;
error_log /var/www/labo-crypto.com/logs/error.log;
root   /var/www/labo-crypto.com/public/;

location / {
index  index.html;
}

error_page  405     =200 $uri;
}
```