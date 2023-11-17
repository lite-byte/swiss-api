// test.js
const swe = require('./build/Release/swe_addon.node');
const obj = swe.Position("11.12.2023");
console.log(obj.Calc());