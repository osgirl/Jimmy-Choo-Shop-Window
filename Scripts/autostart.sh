#!/bin/bash


echo '-> Jimmy Choo App Script'

amixer set PCM -- 100%

echo '-> Starting Jimmy Choo Application'


cd ~/Jimmy-Choo-Shop-Window/OpenFrameworks/JimmyChooShopWindowApp/bin
ret=1
while [ $ret -ne 0 ]; do
    ./JimmyChooShopWindowApp
    ret=$?
done
