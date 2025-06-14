# Lab04 - TLS et certificats
## Partie EMail REFAIRE HESSO adressee 
openssl req -new -config config.conf -out Fullemann-Email.csr -keyout Fullemann-Email.key

openssl req -new -config config-email.conf -out nathan.fulleman@hes-so.ch.csr -keyout nathan.fulleman@hes-so.ch.key

openssl ca -config config-email.conf -in ../mail_client/nathan.fulleman@hes-so.ch.csr -out nathan.fulleman@hes-so.ch.crt

cat ./mail_CA/Fullemann-Email.crt ./HEIG-VDRoot.crt  > CERTIF_CHAIN.crt

openssl pkcs12 -export -name fullemann_p12 \
-inkey nathan.fulleman@hes-so.ch.key \
-in nathan.fulleman@hes-so.ch.crt \
-certfile CERTIF_CHAIN.crt \
-out nathan.fulleman@hes-so.ch.p12

## Partie TLS

openssl req -new -config config.conf -out Fullemann-TLS.csr -keyout Fullemann-TLS.key

openssl req -new -config config-client.conf -out ../TLS_client/IP.csr -keyout ../TLS_client/IP.key

openssl ca -config config.conf -in ../TLS_client/IP.csr -out ../TLS_client/IP.crt -extensions server_reqext

cat ../TLS_client/IP.crt ../TLS_CA/Fullemann-TLS.crt > ../TLS_client/CERTIF_CHAIN.crt

### Configuration nginx
````

server {
    listen 443 ssl http2;
    listen [::]:443 ssl http2;
    
    # Chemins absolus vers les certificats
    ssl_certificate /etc/nginx/CERTIF_CHAIN.crt;
    ssl_certificate_key /etc/nginx/IP.key;
    
    # Protocols supportés
    ssl_protocols TLSv1.2 TLSv1.3;
    
    # Ciphersuites
    ssl_ciphers ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:DHE-RSA-AES128-GCM-SHA256:DHE-RSA-AES256-GCM-SHA384:DHE-RSA-CHACHA20-POLY1305;
    ssl_prefer_server_ciphers off;
    
    ssl_session_timeout 1d;
    ssl_session_cache shared:MozSSL:10m;  # about 40000 sessions
    ssl_session_tickets off;

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
server {
        listen 80 default_server;
        listen [::]:80 default_server;

        return 301 https://$host$request_uri;
}
```
ID : 12
MdP : yBSa74ewRQDfKl3T
ssh -p 2212 labo@secuctfd.iict-heig-vd.in

> passée des données au serveur 
scp -P 2212 ../TLS_client/CERTIF_CHAIN.crt labo@secuctfd.iict-heig-vd.in:~
ssh -p 2212 labo@secuctfd.iict-heig-vd.in
sudo mv ~/CERTIF_CHAIN.crt /etc/nginx/


Ton serveur web sera à l’adresse http://secuctfd.iict-heig-vd.in:8012 ou https://secuctfd.iict-heig-vd.in:44312.