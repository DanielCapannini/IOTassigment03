<?php
echo("test");
echo($_SERVER["REQUEST_METHOD"]);

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    //var_dump($_POST);
    $jsonContent1 = json_decode(file_get_contents("window.json"), true);
    $jsonContent2 = json_decode(file_get_contents("lights.json"), true);
    if ($_POST["type"] == "window") {
        file_put_contents("window.json", json_encode($_POST["date"]));
    } else {
        file_put_contents("lights.json", json_encode($_POST["date"]));
    }
}

