# Projeto IoT com ESP32, Alexa e SinricPro

Este projeto permite controlar uma lâmpada remotamente usando uma placa ESP32, conectada à Alexa por meio da plataforma SinricPro juntamente com a leitura em tempo real da temperatura e umidade através do sensor DHT11. Além disso, uma interface web dinâmica é incorporada para visualizar as leituras e permitir controle manual.

## Funcionalidades Principais

- Controle remoto da lâmpada via Alexa usando SinricPro.
- Monitoramento em tempo real da temperatura e umidade com o sensor DHT11.
- Interface web dinâmica para visualização das leituras e controle manual.

## Componentes Utilizados

- ESP32 para conexão com a Alexa e controle da lâmpada.
- Sensor DHT11 para medição de temperatura e umidade.
- Página web dinâmica para exibir os dados e permitir interações manuais.

## Requisitos

- [Arduino IDE](https://www.arduino.cc/en/Main/Software)
- [Biblioteca SinricPro](https://github.com/sinricpro/esp8266-esp32-sdk)
- [Biblioteca ESP8266WiFi](https://github.com/esp8266/Arduino)
- Conta na [SinricPro](https://portal.sinric.pro/register)
- Dispositivo Alexa (pode ser um Echo, Dot, etc.)

## Configuração do Ambiente

1. Instale a Arduino IDE.
2. Abra a Arduino IDE e vá em **Sketch > Include Library > Manage Libraries**.
3. Pesquise por "SinricPro" e instale a biblioteca.
4. Pesquise por "ESP8266WiFi" e instale a biblioteca.

## Configuração do Projeto

1. Abra o arquivo `main.cpp` no Arduino IDE.
2. Substitua os valores das constantes `WIFI_SSID`, `WIFI_PASS`, `APP_KEY`, `APP_SECRET` com suas credenciais Wi-Fi e SinricPro.
3. Certifique-se de ter o ID do dispositivo correto em `SWITCH_ID`. Caso não tenha, crie um dispositivo na [SinricPro Console](https://portal.sinric.pro/device/list).
4. Verifique a conexão dos pinos `BUTTON_PIN` e `RELE_PIN` de acordo com a sua configuração física.

## Funcionamento

### Funções Principais

- `onPowerState`: É chamada quando o dispositivo é controlado remotamente via SinricPro. Atualiza o estado do dispositivo e aciona o relé.
- `handleButtonPress`: Trata a pressão do botão físico, atualiza o estado do dispositivo e envia o novo estado para o servidor SinricPro.
- `setupWiFi`: Conecta o ESP8266 ao Wi-Fi.
- `setupSinricPro`: Configura a conexão com SinricPro.

### Setup e Loop

- `setup`: Configura as conexões, pinos e inicia as bibliotecas.
- `loop`: Lida com a detecção do botão e verifica constantemente as solicitações da plataforma SinricPro.

## Observações

- O botão físico é conectado ao pino `BUTTON_PIN` e o relé ao pino `RELE_PIN`.
- Certifique-se de ter os drivers corretos para a placa ESP32 na Arduino IDE.
- Certifique-se de ter uma boa conexão Wi-Fi para comunicação com a plataforma SinricPro.

Ao seguir essas etapas, seu dispositivo ESP32 deverá estar pronto para ser controlado remotamente pela Alexa usando a plataforma SinricPro.

## Evidência do funcionamento

https://github.com/Mateus402/sistem-off-projetoiot/assets/112894988/1993db64-12d2-4474-bcb9-fb845c51c383




