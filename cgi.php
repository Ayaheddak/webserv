#!/usr/bin/php-cgi
<?php
header("Content-Type: text/html");

// Get the value of the "name" parameter from the query string
$name = $_GET['name'];

echo "<html><head><title>Greetings</title></head><body>";
echo "<h1>Greetings</h1>";

if ($name) {
  echo "<p>Hello, $name!</p>";
} else {
  echo "<p>Please provide a name parameter in the query string.</p>";
}

echo "</body></html>";
?>
