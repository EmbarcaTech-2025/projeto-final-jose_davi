# Projeto Final: Sistema de Sensoriamento e Controle de Acesso a Ambientes - EmbarcaTech 2025

Autor: **Davi Henrique Vieira Lima e José Augusto Alves de Moraes**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, setembro de 2025

---
## **1. Descrição do Problema**

A gestão de ambientes sensíveis/críticos — como salas de servidores, laboratórios, almoxarifados de alto valor, acervos históricos, entre outros — depende de um controle rigoroso sobre quem acessa o local e das condições em que ele opera. No entanto, as abordagens tradicionais para essa gestão apresentam falhas críticas em três áreas: controle de acesso, auditoria e monitoramento ambiental.

No **controle de acesso**, muitas vezes não há autenticação robusta e integrada, permitindo brechas de segurança. Um grande exemplo desse problema são os roubos de medicamentos controlados, como opioides e vacinas caras, constituindo um problema crônico em hospitais. Muitas vezes, o acesso às farmácias internas é feito com chaves convencionais ou senhas compartilhadas, impossibilitando a identificação do responsável que acessou a área.

Na **auditoria**, a ausência de registros confiáveis e com marcação temporal precisa compromete a rastreabilidade das ações dos usuários. Em casos de acidentes, roubos, entre outros, ter um histórico confiável do acesso dos inidivíduos ao ambiente é essencial para investigações. Frequentemente, em acidentes laborais, a perícia não consegue determinar se o acidente foi causado por erro operacional, falha de manutenção ou sabotagem. Se o acesso à área do acidente fosse registrado, a auditoria mostraria a identidade da última pessoa que acessou o local antes do acidente, direcionando a investigação e fornecendo dados cruciais para o processo. 

Já no **monitoramento ambiental**, dados essenciais como temperatura, umidade, pressão e luminosidade frequentemente não são coletados ou analisados em tempo real, dificultando a prevenção de falhas operacionais. Em 2018, o incêndio do Museu Nacional do Rio de Janeiro, apesar da conjunta falta de monitoramento das condições elétricas, poderia ter seus danos amenizados com o monitoramento das condições do ambiente.

Assim, torna-se necessário um sistema integrado que supere essas limitações e ofereça segurança, confiabilidade e visibilidade completa sobre o ambiente.

---

## **2. Sobre o Projeto**

Este projeto propõe o desenvolvimento de um sistema inteligente e integrado para o sensoriamento e controle de acesso em ambientes sensíveis/críticos, como laboratórios, sala de medicamentos e instalações industriais, onde é crucial monitorar quem acessa o local e sob quais condições ele opera.

Para isso, a solução unifica duas funcionalidades críticas. A primeira é um controle de acesso seguro, realizado por meio de cartões RFID que permitem a identificação confiável do usuário. No caso de uma autorização bem-sucedida, o sistema é capaz de acionar uma fechadura eletromagnética, e uma interface de interação orienta o usuário com feedback imediato. Crucialmente, cada registro de entrada e saída é associado a data e hora e armazenado de forma persistente em um cartão SD dedicado, assegurando uma auditoria histórica completa dos eventos.

Complementarmente, o projeto realiza a coleta contínua de dados ambientais, utilizando sensores de temperatura, pressão, luminosidade e umidade. Essas informações são enviadas via protocolo MQTT para uma interface web, permitindo o acompanhamento remoto e em tempo real das condições do ambiente.

A proposta, portanto, é oferecer uma solução simples, segura e acessível, que integra controle de acesso, auditoria e monitoramento ambiental em um único sistema.

---

## **3. Estrutura do Projeto**
Para garantir a clareza e a manutenibilidade, o projeto foi dividido em diretórios com responsabilidades bem definidas. O código-fonte principal reside na pasta `src`, que por sua vez é modularizada em `app`, `drivers`, `hal...`. A seguir, é apresentada a árvore de arquivos completa com a descrição dos componentes relevantes.
```text
projeto-final-jose_davi/
├── .vscode/                          # Configurações do Visual Studio Code
│   └── ...
├── Etapa 1/                          # Contém o documento da entrega da Etapa 1
│   └── README.md
├── Etapa 2/                          # Contém o documento da entrega da Etapa 2
│   └── README.md
├── Etapa 3/                          # Contém o documento da entrega da Etapa 3
│   └── README.md
├── media/                            # Contém todos os arquivos de mídia do projeto
│   ├── Blocos_Funcionais.png
│   ├── Diagrama_de_Hardware.png
│   ├── Fluxograma_de_Software.png
│   ├── imagem_prototipo.JPG
│   ├── Montagem_escrava.png              
│   └── Montagem_mestre.png   
├── slides/                           # Contém as apresentações do projeto em formato pdf
│   ├── Apresentacão Técnica.pdf      # Apresentação detalhada do projeto
│   └── Elevator Pitch.pdf            # Apresentação resumida do projeto
├── src/                              # Pasta que contém todos arquivos de código do projeto
│   ├── app/                          # Pasta que contém os arquivos principais do projeto
│   │   ├── bitdoglab_escrava.c       # Arquivo principal da BitDogLab Escravo
│   │   ├── bitdoglab_mestre.c        # Arquivo principal da BitDogLab Mestre
│   │   ├── CMakeLists.txt            
│   │   └── rfid_writter.c            # Arquivo principal para gravar dados na ta RFID
│   ├── drivers/                      # Pasta que contém os arquivos para o uso dos periféricos 
│   │   ├── aht10.c                   # Driver para o sensor AHT10 (umidade/temperatura)
│   │   ├── bh1750.c                  # Driver para o sensor BH1750 (luminosidade)
│   │   ├── bmp280.c                  # Driver para o sensor BMP280 (pressão/temperatura)
│   │   ├── buzzer.c                  # Driver para o buzzer
│   │   ├── CMakeLists.txt       
│   │   ├── display_oled.c            # Driver para o display OLED
│   │   ├── hw_config.c               # Implementação da configuração para o leitor de cartão SD.
│   │   ├── led_rgb.c                 # Driver para o LED RGB
│   │   ├── mfrc522.c                 # Driver para o módulo RFID-MFRC522
│   │   ├── sd_card_handler.c         # Handler para o cartão SD
│   │   └── wifi_conn.c               # Implementação para a conexão Wi-Fi
│   ├── hal/                          # Pasta que contém os arquivos de abstração sobre o uso de Hardware
│   │   ├── CMakeLists.txt
│   │   ├── current_time.c            # Implementação para sincronização do RTC
│   │   ├── mqtt_comm.c               # Implementação para a comunicação via MQTT
│   │   └── uart_conn.c               # Implementação para a comunicação via UART
│   ├── include/                      # Pasta que contém todos includes necessários
│   |   ├── inc/                      # Biblioteca para uso do Display Oled
|   |   |   └── ...
│   |   ├── no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/     # Biblioteca para sistema de arquivos FatFS
|   |   |   └── ...
│   │   ├── aht10.h
│   │   ├── bh1750.h
│   │   ├── bmp280.h
│   │   ├── buzzer.h
│   │   ├── current_time.h
│   │   ├── display_oled.h
│   │   ├── i2c_config.h
│   │   ├── led_rgb.h
│   │   ├── lwipopts.h
│   │   ├── mfrc522.h
│   │   ├── mqtt_comm.h
│   │   ├── sd_card_handler.h
│   │   ├── uart_comm.h
│   │   └── wifi_conn.h
│   └── test/                         # Pasta que contém os arquivos para testes unitários com Unity
│       ├── Unity/                    # Biblioteca de testes unitários Unity
│       │   ├── unity_internals.h
│       │   ├── unity.c
│       │   └── unity.h
│       ├── CMakeLists.txt
│       └── tests.c                   # Arquivo com a implementação dos testes unitários
├── .envrc                            # Script para carregar variáveis de ambiente (direnv)
├── .gitignore                        
├── .python-version                   # Especifica a versão do Python para o projeto (pyenv)
├── CMakeLists.txt                    # Arquivo principal de configuração de build do projeto
├── devenv.lock                       # Arquivo para garantir um ambiente de desenvolvimento reprodutível
├── devenv.nix                        # Configuração do ambiente de desenvolvimento usando Nix
├── devenv.yaml                       # Configuração do ambiente de desenvolvimento (devenv)
├── interface.py                      # Script Python da interface web
├── justfile                          # Comandos e scripts para automação de tarefas (Just)
├── LICENSE                           # Arquivo de licença do projeto
├── mbedtls_config.h                  # Arquivo de configuração para a biblioteca mbedTLS (criptografia)
├── pico_sdk_import.cmake             # Script para importar o SDK da Raspberry Pi Pico
├── pyproject.toml                    # Arquivo de configuração para ferramentas Python
├── README.md                         # Documentação principal do projeto
└── uv.lock                           # Arquivo de lock para as dependências Python 

```

## **4. Montagem**

### **4.1. Materiais Utilizados**

| Componente                                    | Quantidade |
| --------------------------------------------- | ---------- |
| **Raspberry Pi Pico W**                       | 2          |
| **Buzzer**                                    | 1          |
| **Display OLED**                              | 1          |
| **LED RGB**                                   | 1          |
| **Módulo Leitor RFID-RC522**                  | 1          |
| **Mini Fechadura Solenoide Eletrônica - 12V** | 1          |
| **Módulo Relé 5V de 1 Canal**                 | 1          |
| **Fonte de Alimentação Externa de 12V**       | 1          |
| **Adaptador P4 Fêmea com Borne**              | 1          |
| **Cartão SD**                                 | 1          |
| **Sensor BH1750**                             | 1          |
| **Sensor AHT10**                              | 1          |
| **Sensor BMP280**                             | 1          |

### **4.2. Esquema de Montagem**

Abaixo pode ser visto o esquema de montagem do projeto, dividido
em um esquema mostrando a placa mestre e os componentes conectados
diretamente a ela e outro esquema mostrando a placa escrava. Caso
queira montar o projeto sem utilizar as placas BitDogLab, utilizando
duas Raspberry Pi Pico W, se refira ao [projeto da BitDogLab](https://github.com/BitDogLab/BitDogLab)
quanto as conexões do buzzer, display OLED e LED RGB.

![Placa Mestre](./media/Montagem_mestre.png)

![Placa Escrava](./media/Montagem_escrava.png)

---

## **5. Diagramas**

### **5.1. Diagrama de Hardware**
O sistema embarcado apresentado adota uma **arquitetura distribuída**, composta por dois módulos BitDogLab, nomeadas **Mestre** e **Escravo**, que operam em conjunto, interligados por meio do protocolo UART. Essa abordagem modular permite uma clara divisão de tarefas, onde o módulo mestre é responsável pelo controle de acesso e interação com o usuário, enquanto o módulo escravo gerencia o armazenamento de dados e a coleta de informações ambientais.

O **módulo BitDogLab (Mestre)** é o cérebro do controle de acesso. Ele se comunica com um Módulo Leitor RFID-RC522 via SPI, que é responsável por detectar a aproximação dos cartões RFID e extrair suas informações. A interação com o usuário é feita através de um **Display OLED (SSD1306)**, conectado via I2C, que exibe instruções e feedback. Para sinalização sonora e visual, o módulo mestre controla um **Buzzer** e um **LED RGB** através de GPIO.

A segurança física do ambiente é controlada por uma **Fechadura Solenoide Eletrônica - 12V**. Essa fechadura é acionada por um **Módulo Relé 5V**, que por sua vez é controlado pelo módulo mestre via GPIO. A alimentação da fechadura é fornecida por uma **Fonte 12V**, conectada através de um **Adaptador P4 Fêmea com Borne**, garantindo a energia necessária para sua operação.

O **módulo BitDogLab (Escravo)** é dedicado ao monitoramento ambiental e ao registro de auditoria. Ele se comunica com o módulo mestre via UART. Para o armazenamento persistente dos registros de acesso, o módulo escravo utiliza um **Cartão SD**, conectado via SPI através de um **Conector IDC**.

O monitoramento das condições ambientais é realizado por um conjunto de sensores conectados ao módulo BitDogLab (Escravo) através de um **I2C Extender**, que permite a conexão de múltiplos dispositivos I2C. Os sensores utilizados são:

* **BMP280**: para medição de temperatura e pressão atmosférica.

* **AHT10**: para aferição da umidade do ambiente.

* **BH1750**: para captar os níveis de luminosidade.

Esses dados são cruciais para garantir a integridade do ambiente sensível/crítico e são coletados e, posteriormente, enviados pelo módulo escravo para uma interface externa via conectividade sem fio (Wi-Fi), conforme descrito nos requisitos anteriormente.

Essa organização do hardware garante uma arquitetura robusta e modular, com uma clara separação de responsabilidades entre os microcontroladores, otimizando o processamento e assegurando que o sistema atenda de forma confiável às suas funções de controle de acesso, auditoria e monitoramento ambiental.

O diagrama apresentado ilustra de maneira clara as conexões entre os componentes físicos, bem como os protocolos de comunicação utilizados:

![Diagrama de Hardware](media/Diagrama_de_Hardware.png)

Em razão da limitação de espaço na imagem acima, segue-se as tabelas das pinagens para ambas BitDogLabs (Mestre e Escravo):

**BitDogLab Mestre**
| GPIO       | Função |
| ----------------- | ---------- |
| **0**         | TX (UART)              |
| **1**         | RX (UART)              |
| **4**         | Controle da Fechadura  |
| **8**         | RST (MFRC522)          |
| **11**        | Cor Verde (LED RGB)    |
| **12**        | Cor Azul (LED RGB)     |
| **13**        | Cor Vermelha (LED RGB) |
| **14**        | SDA (Display OLED)     |
| **15**        | SCL (Display OLED)     |
| **16**        | MISO (MFRC522)         |
| **17**        | CS (MFRC522)           |
| **18**        | SCK (MFRC522)          |
| **19**        | MOSI (MFRC522)         |
| **21**        | Controle do Buzzer     |

<br>

**BitDogLab Escravo**
| GPIO       | Função |
| ----------------- | ---------- |
| **0**         | TX (UART)              |
| **1**         | RX (UART)              |
| **2**         | SDA (Sensores)         |
| **3**         | SCL (Sensores)         |
| **16**        | MISO (Cartão SD)       |
| **17**        | CS (Cartão SD)         |
| **18**        | SCK (Cartão SD)        |
| **19**        | MOSI (Cartão SD)       |

---

### **5.2. Blocos Funcionais**
Como foi mencionado anteriormente, a arquitetura do sistema foi projetada de forma modular para garantir clareza, escalabilidade e manutenibilidade. Dessa forma, cada bloco funcional possui uma responsabilidade específica no fluxo de operação, sendo o sistema coordenado por uma arquitetura de processamento distribuída entre dois microcontroladores. Essa divisão permite um melhor desempenho e organização das tarefas.

A seguir é explicada a funcionalidade de cada bloco:

- **Módulo de Controle de Acesso**: Composto pelo Leitor RFID-RC522, este bloco é a principal interface de identificação do sistema. Sua função é detectar a aproximação de um cartão, ler suas informações de identificação e os dados criptográficos, e enviá-los ao Módulo de Processamento Central para validação. É o ponto de partida para qualquer operação de entrada ou saída do ambiente.

- **Módulo de Feedback**: Consiste na interface de saída de informações para o usuário. Composto pelo Display OLED, LED RGB e Buzzer, este bloco fornece retornos visuais e sonoros, exibindo status da operação, instruções e alertas.

- **Módulo de Atuação Física**: Este módulo é responsável pela resposta física do sistema após a autenticação. É constituído pela Fechadura Solenoide, pelo Módulo Relé e pela Fonte de 12V. Ao receber um comando de acesso autorizado do processador central, ele aciona o relé, que por sua vez energiza a fechadura, permitindo a abertura da porta.

- **Módulo de Dados do Ambiente**: Este módulo é constituído pelos sensores BMP280 (temperatura e pressão), AHT10 (umidade) e BH1750 (luminosidade). Sua função é monitorar continuamente as condições físicas do local, fornecendo dados essenciais que são enviados via Módulo de Conectividade para garantir a integridade do ambiente.

- **Módulo de Armazenamento**: Responsável por guardar os dados de inventário em um Cartão SD. Este módulo garante a persistência das informações, permitindo que o sistema opere de forma offline e mantenha um registro seguro de todas as transações.

- **Módulo de Conectividade**: Utilizando a capacidade Wi-Fi dos microcontroladores, este módulo permite que o sistema se comunique com a rede. Ele é usado pelo Módulo de Processamento Central para obter a data e hora via NTP (garantindo a precisão dos registros) e pelo Módulo de Processamento Secundário para enviar os dados ambientais via protocolo MQTT para uma interface de monitoramento remoto.

- **Módulo de Processamento Secundário**: Neste bloco está o segundo microcontrolador BitDogLab (Escrava), que atua como um processador dedicado para tarefas de suporte. Ele é responsável por gerenciar o Módulo de Dados do Ambiente, coletando as informações dos sensores, e por controlar o Módulo de Armazenamento, recebendo os dados do processador central e gravando-os no Cartão SD.

- **Módulo de Processamento Central**: Representado pelo microcontrolador BitDogLab (Mestre), este bloco funciona como o núcleo do sistema de acesso. Ele recebe os dados do Módulo de Controle de Acesso, executa a lógica de autenticação criptográfica, comanda os Módulos de Atuação Física e de Feedback, e envia os dados do evento para o processador secundário registrar.

A imagem a seguir explicita de forma visual os blocos funcionais do projeto:

![Blocos Funcioanais](media/Blocos_Funcionais.png)

---

### **5.3. Fluxograma do Software**

O diagrama a seguir demonstra o fluxo de processos realizados pelo sistema, mostrando uma
abstração do que será implementado em software, sem distinguir em qual placa será executado
cada processo. 

Este fluxograma demonstra um ciclo completo executado nos loops principais de cada placa do sistema,
começando com a checagem se o leitor RFID identifica algum cartão, se sim o sistema verifica se o
cartão é válido e libera ou bloqueia o acesso conforme o verificado, sinalizando o estado dessa
verificação utilizando o buzzer, o led RGB e o display OLED. Por fim, o sistema obtém os dados dos
sensores e manda esses dados via MQTT para a interface Web, para então repetir este mesmo ciclo
até que o sistema seja desligado.

![Fluxograma de Software](media/Fluxograma_de_Software.png)

## **6. Como Usar**

### **6.1. Compilação**

- Com o VSCode e a extensão [Raspberry Pi Pico](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico):

  Cada placa utilizada no projeto, a mestre e a escrava, possui firmware próprio e para isso é necessário
  indicar qual será o alvo mudando a variável *Device* definida no topo do *CMakeLists.txt* da pasta `src/app`.

  Tendo escolhido o dispositivo desejado basta compilar e passar o código para a placa utilizando a extensão
  oficial da Raspberry Pi Pico para o VScode.

- Pela linha de comando:

  É possível compilar o projeto utilizando apenas a linha de comando utilizando as ferramentas *cmake*, *ninja* e, opcionalmente, o *just*. Caso possua o *just* basta rodar o seguinte comando para compilar o firmware especificado na variável *Device* no *CMakeLists.txt* da pasta `src/app`.

  ```bash
  just build
  ```

  Caso não tenha o just instalado é possível compilar o projeto executando os seguintes comandos na raiz do repositório:

  ```bash
  cmake -G Ninja -S . -B build
  ninja -C build
  ```

  Tendo compilado o projeto, o binário compilado pode ser passado para a placa utilizando o comando:

  ```bash
  just load
  ```

  Ou:

  ```bash
  picotool load -f build/src/app/projeto_final.elf
  ```

### **6.2. Interface MQTT**

Para obter os dados dos sensores via MQTT é preciso configurar um broker e
alterar as configurações do Wi-Fi e do broker no arquivo `bitdoglab_escrava.c`
e no arquivo `interface.py`.

Com tudo configurado, utilize o comando `uv run interface.py` para rodar a interface
pelo computador. Caso não tenha o uv instalado utilize o comando `pip install uv` para
instalá-lo.

### **6.3. Instruções de Uso do Sistema**

Para utilizar o sistema de controle de entrada utilize o programa de registro de cartões que pode ser compilado mudando a variável *Device* no *CMakeLists.txt* da pasta `src/app` para ***RFID_WRITER***. Com os cartões registrados e o sistema corretamente montado e configurado basta aproximar os cartões válidos ao leitor RFID para abrir a fechadura e registrar a entrada e saída do ambiente.

Para obter os dados coletados pelos sensores certifique-se de que o broker MQTT está configurado corretamente e que a placa consegue se conectar ao broker, se for o caso execute a interface pelo computador, seguindo as instruções no tópico acima, para obter os dados dos sensores. 

---

## **7. Destaques Tecnológicos**

Para criar uma solução robusta e inteligente, o projeto integra tecnologias-chave que o diferenciam de sistemas embarcados convencionais. A seguir, detalhamos os destaques tecnológicos do projeto:
* **RFID**: tecnologia de identificação e transferência de dados por meio de ondas de rádio entre um leitor e uma tag. No caso de tags passivas, utilizadas no projeto, não há bateria interna; elas são energizadas pelo campo eletromagnético gerado pelo leitor. Esse campo ativa o chip da tag, que responde transmitindo os dados gravados em sua memória para o leitor. Essa tecnologia foi empregada como base para o controle de acesso e o registro dos usuários.
* **Protocolo NTP**: o *Network Time Protocol* é um protocolo amplamente utilizado para sincronizar relógios em sistemas conectados à rede. No projeto, o microcontrolador conecta-se ao Wi-Fi e envia uma requisição a um servidor NTP, que retorna uma referência de data e hora atualizada. Esses dados são então processados pelo microcontrolador e, assim, o RTC é ajustado corretamente, garantindo o registro preciso dos horários de acesso dos usuários.
* **MQTT**: no projeto, o MQTT foi fundamental para o envio dos dados coletados pelos sensores até a interface web de monitoramento. Ele consiste em um protocolo leve, assíncrono e orientado a mensagens, projetado para dispositivos com recursos limitados. Ele adota a arquitetura publish/subscribe, na qual:
    - o **broker** atua como servidor, intermediando toda a comunicação;
    - o **publisher** é o dispositivo que publica mensagens em tópicos específicos;
    - o **subscriber** é o dispositivo que se inscreve em tópicos para receber mensagens correspondentes.

---

## **8. Imagens e Vídeo Demonstrativos**
A imagem a seguir registra a montagem final do sistema, ilustrando a integração física de todos os componentes que formam o sistema de controle de acesso e monitoramento ambiental. 

Ao centro, destacam-se as **duas placas BitDogLab**, que constituem a arquitetura de processamento distribuída do sistema. Conforme a arquitetura proposta, uma placa foi nomeada como **Mestre**, à direita, responsável por gerenciar a autenticação de usuários e a interface de feedback, enquanto a outra foi nomeada como **Escrava**, à esquerda, dedicada ao monitoramento das condições ambientais e ao armazenamento dos registros de acesso. A comunicação entre ambas é realizada via protocolo **UART**, uma das integrações mais importantes do projeto.

No protótipo, à direita, ligados à BitDogLab Mestre, podemos observar os seguintes periféricos conectados:

* O **Módulo Leitor RFID-RC522** é o principal meio de autenticação do usuário, permitindo a leitura dos cartões de acesso.

* O **Display OLED**, o **LED RGB** e o **Buzzer** compõem o sistema de feedback, fornecendo ao usuário informações visuais e sonoras sobre o status da sua tentativa de acesso.

* A **Fechadura Solenoide** e o **Módulo Relé** são os atuadores que materializam o controle de acesso físico, permitindo ou negando a abertura da porta conforme a autorização.

Já à esquerda, ligados à BitDogLab Escravo, podemos observar os seguintes periféricos conectados:
* O **módulo de Cartão SD**, acoplado à placa Escrava, serve como unidade de armazenamento persistente para o registro de auditoria, gravando cada evento de acesso com data e hora.

* O **conjunto de sensores ambientais (BMP280, AHT10 e BH1750)** é responsável por coletar continuamente os dados de temperatura, umidade, pressão e luminosidade para garantir a integridade do ambiente.

Como um detalhe extra, à direita da BitDogLab Escravo, podemos ver duas tags RFID, utilizadas nos testes do sistema.

Esta montagem representa a materialização do sistema, permitindo a depuração do firmware embarcado e a verificação do funcionamento conjunto de hardware e software, passo crucial para validar a eficácia da solução integrada de segurança, auditoria e monitoramento ambiental.

![Imagem 1 da Montagem](media/imagem_montagem1.JPG)

<br>

Outras imagens do sistema são apresentadas por outros ângulos nas imagens a seguir:
![Imagem 2 da Montagem](media/imagem_montagem2.jpeg)
![Imagem 3 da Montagem](media/imagem_montagem3.jpeg)

<br>

A seguir é apresentado o **vídeo do funcionamento da montagem**:

[Assista ao vídeo no YouTube](https://youtu.be/VB5bjEYOj1M)

---

## **9. Bibliotecas Utilizadas**

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

## **10. Licença**
MIT License
