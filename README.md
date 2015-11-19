# Enviando informaçoes via MQTT

Nesse cenário, construiremos uma pequena aplicação que mandará informações para a plataforma test.mosquitto.org. Essa plataforma nos disponibiliza um Broker MQTT para fazer testes usando o protocolo, e também conta com um exemplo denominado "Demo temperature gauge", o qual oferece um Gauge integrado com um Cliente MQTT.

### Integração da IDE

Primeiramente, para se programar o ESP8266, caso vocês não possuam, é necessário fazer a integração da IDE do Arduino para acrescentar as ferramentas do ESP8266.
Para que isso ocorre sugiro seguir algumas das referências que eu citarei logo abaixo. Mas já adianto que essa integração é bem fácil, simples passos e sua IDE já vai estar pronta para programar o ESP8266 :)

* [https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/installing-the-esp8266-arduino-addon] - Installing the ESP8266 Arduino Addon
* [https://github.com/esp8266/Arduino] - Arduino core for ESP8266 WiFi chip
* [https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/using-arduino-ide] - Using Arduino IDE

### Conexão do ESP ao Modulo Conversor/Placa Arduino
Feito a integração, se faz necessário a ligação do ESP8266 ao modulo conversor usb/serial ou usar uma placa Arduino Uno mesmo(eu uso essa forma)

* [http://pedrominatel.com.br/eletronica/esp8266-o-guia-basico-de-hardware/] - Caso não saiba efetuar a ligação, sugiro esse artigo do Pedro Minatel

### Código a Ser enviado para o ESP8266
* [https://github.com/douglaszuqueto/ESP8266_MQTT/blob/master/test_gauge_mosquitto/test_gauge_mosquitto.ino] - Código está no repositório (pasta  test_gauge_mosquitto);

Com esse código, única coisa que precisa ser feito, é mudar o SSID e a Senha do Roteador WIFI. Feito isso, carrega o código para o ESP8266 e depois abra o Serial Monitor e veja o que está acontecendo.

