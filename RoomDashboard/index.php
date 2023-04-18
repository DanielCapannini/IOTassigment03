<?php

if($_SERVER['REQUEST_METHOD'] == 'POST') {
    $jsonpost = json_decode(file_get_contents('post.json'), true);
    $history["luce"] = end($jsonpost["dati"]["luce"]);
    $history["tapparelle"] = end($jsonpost["dati"]["tapparelle"]);
    echo json_encode($history);
}

if($_SERVER['REQUEST_METHOD'] == 'GET') {
    $jsonpost = json_decode(file_get_contents('post.json'), true);
    $history["luce"] = end($jsonpost["dati"]["luce"]);
    $history["tapparelle"] = end($jsonpost["dati"]["tapparelle"]);
    echo json_encode($history);
}