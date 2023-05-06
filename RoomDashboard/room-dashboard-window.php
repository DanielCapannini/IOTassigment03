<?php
if ($_SERVER["REQUEST_METHOD"] == "GET") {
    $jsonContent1 = json_decode(file_get_contents("window.json"), true);
    $jsonContent2 = json_decode(file_get_contents("lights.json"), true);
    $data["window"] = end($jsonContent1["window"])["state"];
    $data["lights"] = end($jsonContent2["lights"])["state"];
    header("Content-Type: application/json; charset=UTF-8");
    echo json_encode($data);
}