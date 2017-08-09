#!/bin/bash

cd ~/Jimmy-Choo-Shop-Window/OpenFrameworks/JimmyChooShopWindowApp/bin
ret=1
while [ $ret -ne 0 ]; do
    ./JimmyChooShopWindowApp
    ret=$?
done
