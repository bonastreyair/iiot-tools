// HTML web page with temperature value

const char indexHTML[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML>
  <html>
    <head>
        <title>ESP Web Server</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="icon" href="data:,">
        <style>
            html {font-family: Arial; display: inline-block; text-align: center;}
            h2 {font-size: 3.0rem;}
            p {font-size: 3.0rem;}
            body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
            .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
            .switch input {display: none}
            .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
            .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
            input:checked+.slider {background-color: #b30000}
            input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
        </style>
    </head>
    <body>
        <h2>ESP Web Server</h2>
        <h4>Output - GPIO %PIN%</h4>
        <label class="switch">
          <input type="checkbox" onchange="toggleCheckbox(this)" id="%PIN%" %STATE%>
          <span class="slider"></span>
        </label>
        <script>function toggleCheckbox(element) {
            var xhr = new XMLHttpRequest();
            if(element.checked){ 
                xhr.open("GET", "/command?state=1", true);
            } else { 
                xhr.open("GET", "/command?state=0", true); 
            }
            xhr.send();
            }
        </script>
    </body>
  </html>)rawliteral";
