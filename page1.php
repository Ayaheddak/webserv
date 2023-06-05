<html>
<body>

<?php
if(!isset($_COOKIE['test_cookie'])) {
  echo "Cookie named '" . $_COOKIE['test_cookie'] . "' is not set!";
} else {
  echo "Cookie '" . $_COOKIE['test_cookie'] . "' is set!<br>";
  echo "Value is: " . $_COOKIE['test_cookie'];
}
?>

</body>
</html>