# Projeto Final: Etapa 1 (EmbarcaTech 2025) - **Sistema Inteligente para Ambientes Sensíveis/Críticos**

Autor: **Davi Henrique Vieira Lima e José Augusto Alves de Moraes**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, julho de 2025

---

### *Uma Solução Integrada de Controle de Acesso Físico com Registro de Auditoria e Sensores Ambientais*

---

## Descrição do Problema

A gestão de ambientes sensíveis/críticos — como salas de servidores, laboratórios, almoxarifados de alto valor, acervos históricos, entre outros — depende de um controle rigoroso sobre quem acessa o local e das condições em que ele opera. No entanto, as abordagens tradicionais para essa gestão apresentam falhas críticas em três áreas: controle de acesso, auditoria e monitoramento ambiental.

No **controle de acesso**, muitas vezes não há autenticação robusta e integrada, permitindo brechas de segurança. Um grande exemplo desse problema são os roubos de medicamentos controlados, como opioides e vacinas caras, constituindo um problema crônico em hospitais. Muitas vezes, o acesso às farmácias internas é feito com chaves convencionais ou senhas compartilhadas, impossibilitando a identificação do responsável que acessou a área.

Na **auditoria**, a ausência de registros confiáveis e com marcação temporal precisa compromete a rastreabilidade das ações dos usuários. Em casos de acidentes, roubos, entre outros, ter um histórico confiável do acesso dos inidivíduos ao ambiente é essencial para investigações. Frequentemente, em acidentes laborais, a perícia não consegue determinar se o acidente foi causado por erro operacional, falha de manutenção ou sabotagem. Se o acesso à área do acidente fosse registrado, a auditoria mostraria a identidade da última pessoa que acessou o local antes do acidente, direcionando a investigação e fornecendo dados cruciais para o processo. 

Já no **monitoramento ambiental**, dados essenciais como temperatura, umidade, pressão e luminosidade frequentemente não são coletados ou analisados em tempo real, dificultando a prevenção de falhas operacionais. Em 2018, o incêndio do Museu Nacional do Rio de Janeiro, apesar da conjunta falta de monitoramento das condições elétricas, poderia ter seus danos amenizados com o monitoramento das condições do ambiente.

Assim, torna-se necessário um sistema integrado que supere essas limitações e ofereça segurança, confiabilidade e visibilidade completa sobre o ambiente.

---

## Proposta

Diante disso, o presente projeto propõe o desenvolvimento de um sistema integrado para controle de acesso seguro e monitoramento ambiental em tempo real. O acesso é realizado por meio de cartões RFID, que permitem a identificação confiável do usuário, garantindo registros válidos e associados a data e hora.

Esses registros são armazenados em um cartão SD dedicado, assegurando a auditoria histórica das entradas e saídas. Além disso, o sistema conta com uma interface de interação com o usuário, que orienta e fornece feedback imediato sobre as operações realizadas.

No caso de acesso autorizado, o sistema é capaz de acionar uma fechadura eletromagnética, viabilizando a aplicação prática em portas de ambientes que demandam maior controle.

Complementarmente, o projeto realiza a coleta de dados ambientais e os envia, por meio de um mecanismo de conectividade sem fio, para uma interface, permitindo o acompanhamento remoto das condições do ambiente.

A proposta, portanto, é oferecer uma solução simples, segura e acessível, unificando controle de acesso, auditoria e monitoramento ambiental em um único sistema.

---

## Requisitos Funcionais

O sistema deve poder atender os seguintes requisitos funcionais:

| Código | Requisito Funcional |
|--------|-------------------|
| RF01   | O sistema deve ser capaz de detectar a aproximação do cartão RFID e extrair as informações do cartão. |
| RF02   | O sistema deve ser capaz de autenticar o usuário por meio de mecanismo de criptografia. |
| RF03   | O sistema deve ser capaz de abrir a fechadura caso o usuário seja autenticado. |
| RF04   | O sistema deve ser capaz de manter a fechadura fechada caso o usuário seja inválido. |
| RF05   | O sistema deve ser capaz de identificar se a operação do usuário é uma Entrada ou Saída. |
| RF06   | O sistema deve ser capaz de interagir com o usuário, orientando as suas ações e dando feedback a ele. |
| RF07   | O sistema deve ser capaz de obter a data e horário real por meio de mecanismo de conectividade sem fio. |
| RF08   | O sistema deve ser capaz de manter um registro histórico de acesso do usuário, sendo armazenados o nome, a data, o horário e o tipo da operação (Entrada/Saída). |
| RF09   | O sistema deve ser capaz de coletar os seguintes dados ambientais: temperatura, pressão, luminosidade e umidade. |
| RF10   | O sistema deve ser capaz de enviar os dados ambientais para uma interface via mecanismo de conectividade sem fio. |


---

## Requisitos Não-Funcionais

O sistema deve poder atender os seguintes requisitos não-funcionais:

| Código | Requisito Não Funcional |
|--------|------------------------|
| RNF01  | **Confiabilidade**: o sistema deve operar de forma estável e previsível. |
| RNF02  | **Baixa Latência na Validação de Acesso**: o tempo total entre a aproximação do cartão RFID pelo usuário e a resposta final do sistema deve ser a mais baixa possível. |
| RNF03  | **Portabilidade**: o sistema deve ser portátil, ou seja, que pode ser transferido com facilidade. |
| RNF04  | **Baixo Consumo de Energia**: o sistema deve operar com um baixo consumo de energia. |
| RNF05  | **Longo Período de Funcionamento**: o sistema deve ser capaz de operar de forma robusta por longos períodos. |
| RNF06  | **Segurança**: deve ser garantida a autenticidade e integridade dos dados. |
| RNF07  | **Adequada Frequência de Telemetria**: os dados ambientais devem ser lidos e publicados no tópico MQTT com uma frequência adequada de operação. |
| RNF08  | **Escalabilidade**: o sistema deve ser capaz de expandir suas funcionalidades e integrar novos módulos. |
| RNF09  | **Modularidade**: o firmware do projeto deve ser desenvolvido de forma modular. |
| RNF10  | **Usabilidade**: a interface de interação com usuário deve ser fácil e interativa. |

---

## Componentes Utilizados

Para possibilitar a satisfação dos requisitos técnicos do sistema serão utilizados
os seguintes componentes:

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

Observação.: Para esse projeto, também será utilizado um número razoável de **fios e jumpers**.

---

## Especificações

A fim de cumprir os requisitos do projeto, o sistema seguirá as seguintes especificações:

- Utilizando o leitor RFID, o sistema detecta a aproximação do cartão RFID e extrai as informações armazenadas, como nome, CPF e token, garantindo que os dados do usuário estejam disponíveis para autenticação.
- Utilizando mecanismos de criptografia HMAC-SHA256, para cada cartão, o UID é combinado com os dados do usuário (nome e CPF) para gerar um hash criptográfico assinado com uma chave secreta, que é gravado no cartão. Assim, para autenticar o usuário, o sistema recalcula o HMAC com os mesmos dados e compara com o valor armazenado.
- Caso o usuário seja autenticado com sucesso, o sistema aciona a fechadura solenoide, permitindo a abertura da porta de forma segura e temporizada para evitar aquecimento prolongado.
- Caso o usuário não seja autenticado, a fechadura permanece fechada, impedindo o acesso ao ambiente.
- O sistema identifica se a operação do usuário é uma Entrada ou Saída, por meio de uma lista que armazena de forma dinâmica o CPF dos usuário que acessaram o ambiente.
- Utilizando o Display OLED, buzzer e LED RGB, o sistema fornece informações e feedbacks ao usuário, orientando-o sobre as operações e indicando sucesso ou falha na autenticação.
- Utilizando conectividade Wi-Fi, o sistema realiza uma requisição NTP a "pool.ntp.org" e, assim, obtém a data e horário reais, garantindo que todos os registros sejam carimbados com informações temporais precisas.
- O sistema mantém um registro histórico de acesso do usuário, armazenando nome, data, horário e tipo de operação (Entrada/Saída) em um cartão SD, permitindo auditoria e rastreabilidade.
- A temperatura (sensor BMP280), pressão (sensor BMP280), umidade (sensor AHT10) e luminosidade (sensor BH1750) são capturadas de forma contínua, fornecendo monitoramento ambiental do local.
- Utilizando conectividade Wi-Fi e protocolo MQTT, os dados ambientais são enviados a um tópico específico, sendo recebidos por um script Python que exibe essas informações em uma interface, permitindo monitoramento remoto em tempo real. (Observação: a interface não é um dos focos de apresentação do projeto. Ela apenas exemplifica uma aplicação válida e prática de umas das funcionalidades do projeto)

---

## Referências
- **Integrated Security and Environmental Monitoring in Critical Facilities**  

  *Fonte: ResearchGate, 2019*

- **Smart Building and Environmental Monitoring** 

  *Fonte: MDPI, 2021* 

- **Security Issues in RFID-based Access Control Systems**  
 
  *Fonte: IEEE Xplore, 2019*