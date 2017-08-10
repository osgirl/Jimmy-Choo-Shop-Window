#!/bin/bash

#-----------------------------------------------------------
#
# start Jimmy Choo Application
#
#-----------------------------------------------------------

echo '-> Jimmy Choo App Script'

amixer set PCM -- 100%

echo '-> Starting Jimmy Choo Application'

while true; do
  ~/Jimmy-Choo-Shop-Window/OpenFrameworks/JimmyChooShopWindowApp/bin/JimmyChooShopWindowApp &
  wait $!
  sleep 10
done
exit