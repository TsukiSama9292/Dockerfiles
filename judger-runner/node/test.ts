function runSum() {
  let sum = 0;
  for (let i = 0; i < 10_000_000; i++) {
    sum += i;
  }
  console.log("Sum:", sum);
}

runSum();