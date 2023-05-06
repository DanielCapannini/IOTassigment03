<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $jsonContent1 = json_decode(file_get_contents("window.json"), true);
    $jsonContent2 = json_decode(file_get_contents("lights.json"), true);
    if ($_POST["type"] == "window") {
        $data=array("state"=>$_POST["state"],"start"=>$_POST["start"]);
        $jsonContent1["window"][count(end($jsonContent1))-1]["end"]=$_POST["start"];
        array_push($jsonContent1["window"], $data);
        file_put_contents("window.json", json_encode($jsonContent1, JSON_PRETTY_PRINT));
    } else {
        $data=array("state"=>$_POST["state"],"start"=>$_POST["start"]);
        $jsonContent2["lights"][count(end($jsonContent2))-1]["end"]=$_POST["start"];
        array_push($jsonContent2["lights"], $data);
        file_put_contents("lights.json", json_encode($jsonContent2, JSON_PRETTY_PRINT));
    }
}