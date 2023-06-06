<?php
session_start();

// Display the session and cookie values
echo "Session Username: " . $_SESSION['username'] . "<br>";
echo "Cookie User ID: " . $_COOKIE['user_id'] . "<br>";
?>
