<?php
// 測試用
$sum = 0;
for ($i = 0; $i < 10000000; $i++) {
    $sum += $i;
}
echo "Sum: " . $sum . PHP_EOL;