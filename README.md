# Enviando informações via MQTT

Nesse cenário, construiremos uma pequena aplicação que mandará informações para a plataforma test.mosquitto.org. Essa plataforma nos disponibiliza um Broker MQTT para fazer testes usando o protocolo, e também conta com um exemplo denominado "Demo temperature gauge", o qual oferece um Gauge integrado com um Cliente MQTT.

### Integração da IDE

Primeiramente, para se programar o ESP8266, caso vocês não possuam, é necessário fazer a integração da IDE do Arduino para acrescentar as ferramentas do ESP8266.
Para que isso ocorra, sugiro seguir algumas das referências que eu citarei logo abaixo. Mas já adianto que essa integração é bem fácil, simples passos e sua IDE já vai estar pronta para programar o ESP8266 :)

* [https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/installing-the-esp8266-arduino-addon] - Installing the ESP8266 Arduino Addon
* [https://github.com/esp8266/Arduino] - Arduino core for ESP8266 WiFi chip
* [https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/using-arduino-ide] - Using Arduino IDE

**OBS**: Precisará baixar essa biblioteca também ;) [https://github.com/knolleary/pubsubclient]

### Conexão do ESP ao Modulo Conversor/Placa Arduino
Feito a integração, se faz necessário a ligação do ESP8266 ao modulo conversor usb/serial ou usar uma placa Arduino Uno mesmo(eu uso essa forma)

* [http://pedrominatel.com.br/eletronica/esp8266-o-guia-basico-de-hardware/] - Caso não saiba efetuar a ligação, sugiro esse artigo do Pedro Minatel.

### Código a Ser enviado para o ESP8266
* [https://github.com/douglaszuqueto/ESP8266_MQTT/blob/master/test_gauge_mosquitto/test_gauge_mosquitto.ino] - Código está no repositório (pasta  test_gauge_mosquitto);

Com esse código, única coisa que precisa ser feito, é mudar o SSID e a Senha do Roteador WIFI. Feito isso, carregue o código para o ESP8266 e depois abra o Monitor Serial e veja o que está acontecendo.
Na imagem abaixo, pode-se observar que deu tudo certo, pois se conectou a rede WIFI, se conectou com o Broker(test.mosquitto.org) e já começou a puplicar a mensagem.

![ScreenShot](https://raw.github.com/douglaszuqueto/ESP8266_MQTT/master/Monitor_Serial.png)

### Visualizando Resultados

Para ver se realmente deu certo, abra o site[http://test.mosquitto.org/gauge/] e veja se o Gauge está mudando de valor a cada segundo e incrementando de 1 em 1.
Observe a imagem abaixo com o site já aberto.

![ScreenShot](https://raw.github.com/douglaszuqueto/ESP8266_MQTT/master/VisualizandoTesteMQTT.png)

O MQTT é um protocolo muito bom para diversos tipos de aplicações, pois é leve, rápido, tem uma enorme compatibilidade com os embarcados e também possui inúmeras ferramentas para trabalhar com MQTT. 
Abaixo, deixarei uma lista de algumas referências caso queiram estudar o MQTT, sugiro também, caso tenha curiosidade, pesquisar no YouTube por vídeos de Arduino + MQTT, ESP8266 + MQTT. 

* [http://mosquitto.org/] 
* [http://test.mosquitto.org/]
* [http://www.eclipse.org/paho/]
* [http://mqtt.org/]
* [https://www.cloudmqtt.com/] - Plataforma que te oferece uma conta free para realizar alguns testes :)
* [www.hivemq.com/blog/mqtt-essentials-part-1-introducing-mqtt] - Série de artigos sobre MQTT **Recomendo**

### Observações
Estou usando esse protocolo em meu TCC. De acordo que vou terminando o projeto, irei postando mais detalhes no grupo.
Ontem, deixei meu Embarcado ligado das 8 horas da manhã, até as 6:30 da tarde, ele estava enviando mensagens a cada segundo para o Broker, deve ter dado pelos meus cálculos, mais de 40.000 mensagens enviadas haha.

### Contato
Caso queiram mais informações, ajuda ou trocar uma ideia, podem me adicionar no Facebook [https://www.facebook.com/douglasalin] , ou me mandar um e-mail diretamente: douglas.zuqueto@gmail.com

E contribuam para o grupo[https://www.facebook.com/groups/arduino.br] também, postando seus projetos :)

**Um Grande Abraço, Douglas Salin Zuqueto**



