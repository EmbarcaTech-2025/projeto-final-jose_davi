# Projeto Final: Sistema de Sensoriamento e Controle de Acesso a Ambientes - EmbarcaTech 2025

Autor: **Davi Henrique Vieira Lima e José Augusto Alves de Moraes**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, agosto de 2025

---

## **Sobre o Projeto**

Este projeto se trata de um sistema inteligente para o sensoriamento
e o controle de entrada de ambientes de acesso restrito, como laboratórios
e ambientes industriais em que é importante saber quem está tendo acesso ao local
e quais as condições do ambiente.

Para isso, criamos um sistema que usa um sensor RFID para registrar a entrada e saída
de pessoas, além de sensores de temperatura, pressão e umidade. Os dados do ambiente são
mandados via MQTT para serem visualizados por uma interface Web, enquanto os registros de
entrada e saída são armazenados internamente.

---

## **Bibliotecas Utilizadas**

- [pico-sdk](https://github.com/raspberrypi/pico-sdk)

  Autor: [Raspberry Pi](https://github.com/raspberrypi)

- [no-OS-FatFS-SD-SPI-RPi-Pico](https://github.com/carlk3/no-OS-FatFS-SD-SPI-RPi-Pico/tree/sdio)

  Autor: [Carl J Kugler III](https://github.com/carlk3)

- [Unity](https://github.com/ThrowTheSwitch/Unity)

  Autor: [Throw The Switch](https://github.com/ThrowTheSwitch)

- [Driver AHT10](https://github.com/jrfo-hwit/hlab/tree/main/firmware/c_cpp/examples/3_aht10_i2c_uart0)

  Autor: [Juliano Oliveira](https://github.com/jrfo-hwit)

- [Driver BH1750](https://github.com/jrfo-hwit/hlab/tree/main/firmware/c_cpp/examples/7_bh1750_i2c_uart0)

  Autor: [Juliano Oliveira](https://github.com/jrfo-hwit)

- [Driver BMP280](https://github.com/jrfo-hwit/hlab/tree/main/firmware/c_cpp/examples/4_bmp280_i2c_uart0)

  Autor: [Juliano Oliveira](https://github.com/jrfo-hwit)

- [Driver MFRC522](https://github.com/BenjaminModica/pico-mfrc522.git)

  Autor: [Benjamin Modica](https://github.com/BenjaminModica)

---

## **Montagem**

### **Materiais Utilizados**

| Componente        | Quantidade |
| ----------------- | ---------- |
| **Raspberry Pi Pico W**            | 2          |
| **Buzzer**            | 1          |
| **Display OLED**      | 1          |
| **LED RGB**           | 1          |
| **Módulo Leitor RFID-RC522**            | 1          |
| **Mini Fechadura Solenoide Eletrônica - 12V**           | 1          |
| **Módulo Relé 5V de 1 Canal**           | 1          |
| **Fonte de Alimentação Externa de 12V**           | 1          |
| **Adaptador P4 Fêmea com Borne**           | 1          |
| **Cartão SD**         | 1          |
| **Sensor BH1750**     | 1          |
| **Sensor AHT10**      | 1          |
| **Sensor BMP280**     | 1          |

### **Esquema de Montagem**

Abaixo pode ser visto o esquema de montagem do projeto, dividido
em um esquema mostrando a placa mestre e os componentes conectados
diretamente a ela e outro esquema mostrando a placa escrava. Caso
queira montar o projeto sem utilizar as placas BitDogLab, utilizando
duas Raspberry Pi Pico W, se refira ao [projeto da BitDogLab](https://github.com/BitDogLab/BitDogLab)
quanto as conexões do buzzer, display OLED e LED RGB.

![Placa Mestre](./media/Montagem_mestre.png)

![Placa Escrava](./media/Montagem_escrava.png)

---

### **Destaques Tecnológicos**
Para criar uma solução robusta e inteligente, o projeto integra tecnologias-chave que o diferenciam de sistemas embarcados convencionais. A seguir, detalhamos os destaques tecnológicos do projeto:
* **RFID**: tecnologia de identificação e transferência de dados por meio de ondas de rádio entre um leitor e uma tag. No caso de tags passivas, utilizadas no projeto, não há bateria interna; elas são energizadas pelo campo eletromagnético gerado pelo leitor. Esse campo ativa o chip da tag, que responde transmitindo os dados gravados em sua memória para o leitor. Essa tecnologia foi empregada como base para o controle de acesso e o registro dos usuários.
* **Protocolo NTP**: o *Network Time Protocol* é um protocolo amplamente utilizado para sincronizar relógios em sistemas conectados à rede. No projeto, o microcontrolador conecta-se ao Wi-Fi e envia uma requisição a um servidor NTP, que retorna uma referência de data e hora atualizada. Esses dados são então processados pelo microcontrolador e, assim, o RTC é ajustado corretamente, garantindo o registro preciso dos horários de acesso dos usuários.
* **MQTT**: no projeto, o MQTT foi fundamental para o envio dos dados coletados pelos sensores até a interface web de monitoramento. Ele consiste em um protocolo leve, assíncrono e orientado a mensagens, projetado para dispositivos com recursos limitados. Ele adota a arquitetura publish/subscribe, na qual:
    - o **broker** atua como servidor, intermediando toda a comunicação;
    - o **publisher** é o dispositivo que publica mensagens em tópicos específicos;
    - o **subscriber** é o dispositivo que se inscreve em tópicos para receber mensagens correspondentes.

---

## **Como Usar**

### **Compilação**

- Com o VSCode e a extensão [Raspberry Pi Pico](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico):

  Cada placa utilizada no projeto, a mestre e a escrava, possui firmware próprio e para isso é necessário
  indicar qual será o alvo mudando a variável *Device* definida no topo do CMakeLists.txt da pasta `src/app`.

  Tendo escolhido o dispositivo desejado basta compilar e passar o código para a placa utilizando a extensão
  oficial da Raspberry Pi Pico para o VScode.

- Pela linha de comando:

  É possível compilar o projeto utilizando apenas a linha de comando utilizando as ferramentas *cmake*, *ninja*
  e, opcionalmente, o *just*. Caso possua o *just* basta rodar o comando `just build MASTER` para compilar o
  firmware da placa mestre ou `just build SLAVE` para a placa escrava. Caso o *just* não esteja instalado basta
  copiar os comandos definidos no *justfile* presente na raiz do repositório, substituindo `{{ device }}` por `MASTER`
  ou `SLAVE`.

  Tendo compilado o projeto, o binário compilado pode ser passado para a placa utilizando o comando
  `picotool load -f build/src/app/projeto_final.elf`.

### **Interface MQTT**

Para obter os dados dos sensores via MQTT é preciso configurar um broker e
alterar as configurações do Wi-Fi e do broker no arquivo `bitdoglab_escrava.c`
e no arquivo `interface.py`.

Com tudo configurado, utilize o comando `uv run interface.py` para rodar a interface
pelo computador. Caso não tenha o uv instalado utilize o comando `pip install uv` para
instalá-lo.

### **Instruções de Uso do Sistema**

---

## **Imagens e Vídeo Demonstrativos**

---
