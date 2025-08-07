# Projeto Final: Etapa 1 - EmbarcaTech 2025

Autor: **Davi Henrique Vieira Lima e José Augusto Alves de Moraes**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, julho de 2025

---

## Descrição do Problema

Atualmente, o controle de estoque é um dos principais desafios enfrentados
por empresas de diversos setores, impactando diretamente a eficiência operacional,
os custos logísticos, a lucratividade e até mesmo a satisfação do cliente.
Um estoque mal gerenciado pode causar desde a falta de produtos essenciais,
comprometendo vendas e a reputação da empresa, até o excesso de mercadorias paradas,
que ocupam espaço, imobilizam capital e geram desperdícios.

Ainda é comum o uso de técnicas manuais, como planilhas eletrônicas e pranchetas,
para a gestão de estoque, o que dificulta o acompanhamento preciso de inventários
sujeitos a flutuações constantes. Essa abordagem torna o processo mais lento,
impreciso e vulnerável a erros humanos, como registros incorretos, perdas por
vencimento e falhas na previsão de demanda, comprometendo a reposição adequada e
gerando prejuízos financeiros consideráveis.

Além disso, a falta de visibilidade em tempo real sobre o estado dos estoques
prejudica a tomada de decisões estratégicas, como a negociação com fornecedores,
o planejamento de compras e a resposta a oscilações de mercado. Em empresas que
operam com grande variedade de itens, como redes varejistas e indústrias, a
complexidade do controle se torna ainda maior.

Diante de um cenário de digitalização acelerada e aumento da competitividade,
torna-se essencial a adoção de sistemas automatizados e inteligentes. Essas
ferramentas não apenas asseguram um controle mais preciso e ágil, como também
permitem previsões de demanda, alertas automáticos de reposição, rastreabilidade
de produtos e redução significativa de perdas e desperdícios.

Portanto, investir na modernização do controle de estoque não é apenas uma escolha
estratégica, mas uma necessidade para a sobrevivência e crescimento sustentável das
empresas no contexto atual.

---

## Proposta

Com o objetivo de mitigar a problemática mencionada, este trabalho propõe o
desenvolvimento de uma solução automatizada para controle de estoque, por meio
de um sistema capaz de identificar produtos utilizando a leitura de QR Codes e
registrar, de forma precisa, quais itens estão disponíveis e em que quantidade.

O sistema também possibilita a interação com o usuário por meio de um teclado
matricial, permitindo o registro da quantidade de um determinado produto a ser
incluído ou removido do estoque, de forma prática e eficiente.

Além disso, o sistema possui um mecanismo de conectividade que possibilita a
comunicação com um sistema externo, enviando mensagens com informações relevantes
para o gerenciamento do estoque — como a quantidade de itens adicionados ou
retirados, a data e hora da operação, entre outros dados — contribuindo para um
controle mais completo, seguro e integrado.

Como conclusão, o desenvolvimento deste sistema representa uma alternativa viável
e eficiente para modernizar o controle de estoque, reduzindo falhas humanas, aumentando
a precisão das informações e promovendo maior integração entre os processos internos e
externos das organizações. Ao aliar tecnologias como leitura de QR Codes, interface com
teclado matricial e conectividade com sistemas externos, a solução proposta demonstra
potencial para atender às demandas de um cenário empresarial cada vez mais dinâmico e
automatizado, contribuindo significativamente para a otimização da gestão de inventário.

---

## Requisitos Funcionais

O sistema deve poder atender os seguintes requisitos funcionais:

- Identificar o produto com base em seu QR Code.
- Indicar ao usuário se a identificação do produto foi possível.
- Armazenar e atualizar a quantidade de produtos.
- Permitir a interação com usuário para que ele tanto adicione produtos quanto remova produtos.
- Permitir ao usuário a definição da quantidade de produtos que ele quer adicionar ou remover.
- Indicar ao usuário, visualmente, se o sistema está operando em modo para adicionar produtos ou para remover produtos.
- Enviar e receber dados sobre o estoque via MQTT.

---

## Requisitos Não-Funcionais

O sistema deve poder atender os seguintes requisitos não-funcionais:

- Confiabilidade: o sistema deve operar de forma estável e previsível.
- Portabilidade: o sistema deve ser portátil, ou seja, que pode ser transferido com facilidade.
- Baixo Consumo de Energia: o sistema deve operar com um baixo consumo de energia.
- Longo Período de Funcionamento: o sistema deve ser capaz de operar de forma robusta por longos períodos.
- Segurança: deve ser garantido a autenticidade e integridade dos dados.
- Escalabilidade: o sistema deve ser capaz de expandir suas funcionalidades e integrar novos módulos.
- Usabilidade: a interface de interação com usuário deve ser fácil e interativa.

---

## Componentes Utilizados

Para possibilitar a satisfação dos requisitos técnicos do sistema serão utilizados
os seguintes componentes, alguns presentes na BitDogLab, outros não:

| Componente        | Quantidade |
| ----------------- | ---------- |
| Buzzer            | 1          |
| Câmera OV2640     | 1          |
| Cartão SD         | 1          |
| Display OLED      | 1          |
| LED RGB           | 1          |
| Teclado Matricial | 1          |

---

## Especificações

A fim de cumprir os requisitos funcionais, o sistema seguirá as seguintes especificações:

- Utilizando a Câmera OV2640, o sistema identifica o produto por meio de seu QR Code e faz o registro do produto que está sendo apresentado.
- Utilizando o teclado matricial, o usuário pode especificar ao sistema se ele quer adicionar ou remover o produto e a quantidade do produto considerado.
- Utilizando o Display OLED será apresentado ao usuário informações sobre o produto, instruções para realizar as diversas operações permitidas pelo sistema, entre outras informações.
- O cartão SD será utilizado a fim de armazenar informações sobre o estoque local, permitindo a operação do sistema mesmo em caso de queda do servidor central.
- O sistema enviará feedbacks extras, além do Display OLED, ao usuário acerca de suas operações por meio de um buzzer e um LED RGB. Exemplo: após a leitura do QR Code, o sistema indicará que o produto foi identificado por meio do som do buzzer e a cor verde do LED RGB.
- Por meio do módulo Wi-Fi da BitDogLab, utilizando o protocolo MQTT, o sistema será capaz de enviar e receber dados acerca da quantidade de determinado produto no estoque, número de produtos adicionados ou retirados, entre outros.
