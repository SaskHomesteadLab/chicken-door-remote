R"html(

<!DOCTYPE html>
<html>

<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
  <style>

    body {
      font-family: "Lucida Console", "Courier New", monospace;
    }

    h1 {
      text-align: center;
    }

    .center_div {
      border: 3px solid black;
      border-radius: 24px;
      margin-left: auto;
      margin-right: auto;
      width: 50%;
      background-color: #808080;
      text-align: center;
      padding: 8px;
    }

    .btn_div {
      text-align: center;
      padding: 8px;
    }

    button {
      border-radius: 12px;
      border: 2px solid #AB5DC8;
      background-color: #40CFA9;
      color: #AB5DC8;
      text-align: center;
      padding: 15px 32px;
      display: inline-block;
      font-size: 200px;
      box-shadow: 0 9px #999;
    }

    button:active {
      background-color: #3CC19E;
      box-shadow: 0 5px #666;
      transform: translateY(4px);
    }
  </style>
</head>

<body>
  <h1>Chicken Door Remote</h1>
  <div class="center_div">
    <div class="btn_div">
      <button onclick="backgroundCall('/open');">&#9650;</button>
    </div>
    <div class="btn_div">
      <button onclick="backgroundCall('/close');">&#9660;</button>
    </div>
    <div class="btn_div">
      <button onclick="backgroundCall('/stop');">&#11200;</button>
    </div>
  </div>
  <script>
    function backgroundCall(path) {
      var xhr = new XMLHttpRequest();
      xhr.open('GET', path, true);
      xhr.send();
    };
  </script>
</body>

</html>

)html"
