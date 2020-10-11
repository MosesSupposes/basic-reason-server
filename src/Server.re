open Serbet.Endpoint;
open Async; // this comes with Serbet

module HelloEndpoint = {
  [@decco.decode]
  type params = {name: string};

  let endpoint =
    Serbet.endpoint({
      verb: GET,
      path: "/hello/:name",
      handler: req => {
        let%Async params = req.requireParams(params_decode);
        OkString("Hello there, " ++ params.name)->async;
      },
    });
};

module HelloJsonEndpoint = {
  [@decco.decode]
  type body_in = {name: string};

  [@decco.encode]
  type body_out = {message: string};

  let endpoint =
    Serbet.jsonEndpoint({
      verb: POST,
      path: "/hello/json",
      body_in_decode,
      body_out_encode,
      handler: (body, _req) => {
        {message: "Hey there, " ++ body.name}->async;
      },
    });
};

let app =
  Serbet.application([HelloEndpoint.endpoint, HelloJsonEndpoint.endpoint]);
