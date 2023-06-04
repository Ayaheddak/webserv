<?php
while(1);
$cookie_name = "user";
$cookie_value = "thats meeee";
setcookie($cookie_name, $cookie_value, time() + (86400 * 30), "/");
?>
