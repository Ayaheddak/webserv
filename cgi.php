<?php
// Set a cookie\
while(1);
$cookie_name = "test_cookie";
$cookie_value = "Hello, World!";
$expiration = time() + (24 * 60 * 60); // Expiration time: 24 hours
$path = "/"; // Cookie path

setcookie($cookie_name, $cookie_value, $expiration, $path);

// Check if the cookie is set
// if (isset($_COOKIE[$cookie_name])) {
//     echo "Cookie '" . $cookie_name . "' is set!<br>";
//     echo "Cookie value: " . $_COOKIE[$cookie_name];
// // } else {
//     echo "Cookie '" . $cookie_name . "' is not set!";
// }
?>