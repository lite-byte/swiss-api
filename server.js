const http = require('node:http');
const swe = require('./build/Release/swe_addon.node');

const obj = swe.Position("11.12.2023");

const hostname = '13.91.141.66';
const port = 3000;

const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  res.end(obj.Calc());
});

server.listen(port, '0.0.0.0', () => {
  console.log(`Server running at http://${hostname}:${port}/`);
}); 