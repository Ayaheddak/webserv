<?php
session_start();
?>
<!DOCTYPE html>
<html>
<body>

<?php
// Echo session variables that were set on previous page
if (isset($_SESSION["favcolor"]))
    echo "Favorite color is " . $_SESSION["favcolor"] . ".<br>";
else 
    echo("favColor is not set" . "<br>");
if (isset($_SESSION["favanimal"]))
    echo "Favorite animal is " . $_SESSION["favanimal"] . ".";
else
    echo("favAnimal is not set" . "<br>");
?>
</html>
</body>