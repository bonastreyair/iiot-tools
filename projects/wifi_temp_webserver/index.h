// HTML web page with temperature value

const char indexHTML[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML><html><head>
    <title>Temperature Output</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    </head><body>
    <h2>Temperature</h2> 
    <h3>%TEMPERATURE% &deg;C</h3>
  </body></html>)rawliteral";