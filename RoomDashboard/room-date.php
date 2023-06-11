<?php
$data = json_decode(file_get_contents("php://input"), true);
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $jsonContent1 = json_decode(file_get_contents("window.json"), true);
    $jsonContent2 = json_decode(file_get_contents("lights.json"), true);
    if ($data["type"] == "window") {
        $data2=array("state"=>$data["state"],"start"=>$data["start"]);
        $jsonContent1["window"][count(end($jsonContent1))-1]["end"]=$data["start"];
        array_push($jsonContent1["window"], $data2);
        file_put_contents("window.json", json_encode($jsonContent1, JSON_PRETTY_PRINT));
    } else {
        $data2=array("state"=>$data["state"],"start"=>$data["start"]);
        $jsonContent2["lights"][count(end($jsonContent2))-1]["end"]=$data["start"];
        array_push($jsonContent2["lights"], $data2);
        file_put_contents("lights.json", json_encode($jsonContent2, JSON_PRETTY_PRINT));
    }
}