Commencer
1. git clean -fdx
2. git reset --hard HEAD
3. git fetch upstream
4. git checkout labXX

Compilation
1. make init
2. make
3. ./st

Rendu
1. git add *
2. git status
3. git commit -m "End of labXX"
4. git push -u origin

Docker
1. docker build --build-arg USERID=$(id -u) --build-arg GROUPID=1000 -t so3_env . 
2. docker run --privileged -v /dev:/dev -v "$(pwd)":/home/reds/so3 -w /home/reds/so3 -it so3_env