<?php

$date = json_decode(file_get_contents('php://input'), true);


if($_SERVER['REQUEST_METHOD'] == 'GET') {
    $jsonpost = json_decode(file_get_contents('post.json'), true);
    $data["luce"] = end($jsonpost["dati"]["luce"]);
    $data["tapparelle"] = end($jsonpost["dati"]["tapparelle"]);
    echo json_encode($data);
}