<?php
session_start();

// Set a session variable
// set the session variable 'username' to 'BettyW'
$_SESSION['username'] = 'BettyW';
$_SESSION['first_name'] = 'Betty';

// Set a cookie
$cookie_name = 'user_id';
$cookie_value = '123';
$cookie_expiration = time() + (86400 * 30); // Expires in 30 days
setcookie($cookie_name, $cookie_value, $cookie_expiration, '/'); // '/' indicates the entire website path

?>
