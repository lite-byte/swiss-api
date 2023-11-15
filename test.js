// test.js
const swe = require('./build/Release/swe');

const obj = swe.Position("11.12.2023");
console.log(obj.Calc());