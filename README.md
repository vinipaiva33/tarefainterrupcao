# Projeto: Controle de Animações em Matriz de LEDs via Interrupções no Raspberry Pi Pico W

## Descrição Geral

Este projeto foi desenvolvido para demonstrar o controle de uma matriz de LEDs (do tipo WS2812, 5x5) utilizando o microcontrolador Raspberry Pi Pico W e a ferramenta educacional BitDogLab. O sistema permite a navegação entre diferentes padrões de animação (representados em um buffer interno) por meio da utilização de botões.

- **Botão A (GPIO definido em `BUTTON_A`)**: Ao ser pressionado, incrementa o valor da variável `numero` (limitada a 9) e atualiza a exibição na matriz de LEDs com a função `set_one_led()`.
- **Botão B (GPIO definido em `BUTTON_B`)**: Ao ser pressionado, decrementa o valor da variável `numero` (até 0) e atualiza a exibição na matriz.
- **LED de Status**: Em paralelo, um LED conectado ao pino `PIN_LED_R` é controlado de forma repetitiva (pisca continuamente) em um loop infinito, servindo como indicação de que o firmware está em execução.

O projeto utiliza duas bibliotecas próprias:
- **inicia.h** – Responsável por configurar a matriz de LEDs WS2812 (através do periférico PIO) e fornecer funções auxiliares, como `set_one_led()`, que atualiza o estado da matriz com base em um buffer interno de 5x5.
- **iniciapino.h** – Realiza a inicialização dos pinos de entrada e saída da BitDogLab, configurando o LED RGB (utilizando o pino definido em `PIN_LED_R`) e os botões (configurados com pull-up).

O controle dos eventos dos botões é realizado por meio de interrupções (via `gpio_set_irq_enabled_with_callback()`). A função de callback `gpio_irq_handler()` trata os eventos de borda de descida, implementando um debouncing de 200 ms. Assim, ao detectar um acionamento do botão A, o programa incrementa o valor de `numero` (se não estiver no limite superior) e atualiza a matriz de LEDs; de forma similar, o botão B decrementa o valor (se não estiver no limite inferior).

Além disso, o código utiliza os recursos do SDK Pico (incluindo funções de temporização e de controle dos pinos GPIO) e das bibliotecas de hardware para o controle dos LEDs endereçáveis.

## Componentes do Projeto

- **Microcontrolador**: Raspberry Pi Pico W (RP2040)
- **Plataforma Educacional**: BitDogLab
- **Matriz de LEDs**: WS2812 – 5x5 (configurada via PIO)
- **Botões**: Dois botões (A e B) conectados aos pinos definidos (ex.: `BUTTON_A` e `BUTTON_B`)
- **LED de Status**: LED RGB conectado ao pino `PIN_LED_R`
- **Bibliotecas Utilizadas**:
  - Pico SDK: `pico/stdlib.h`, `hardware/pio.h`, `hardware/clocks.h`
  - Bibliotecas customizadas: `inicia.h`, `iniciapino.h`
- **Ferramentas de Desenvolvimento**: VS Code com extensão para Raspberry Pi Pico e integração com o simulador Wokwi.

## Funcionalidades Implementadas

- **Interrupções via GPIO**: O sistema utiliza interrupções para detectar o acionamento dos botões com debouncing (200 ms), garantindo que leituras espúrias (bouncing) não afetem a contagem.
- **Controle da Matriz de LEDs**: A função `set_one_led(uint8_t r, uint8_t g, uint8_t b, int numero)` recebe valores de cor (intensidades de vermelho, verde e azul) e um índice (variável `numero`) para selecionar o padrão de LED a ser exibido. O padrão é definido em um buffer booleano 5x5 presente na biblioteca `inicia.h`.
- **Loop de Status**: Um loop infinito no `main()` mantém o LED de status (conectado a `PIN_LED_R`) piscando com um delay configurado pela variável `tempo`.

## Como Compilar e Simular

1. **Ambiente de Desenvolvimento**:  
   - Utilize o Visual Studio Code com o Pico SDK configurado e as extensões necessárias para o Raspberry Pi Pico.
   - Certifique-se de que o simulador Wokwi esteja integrado ao VS Code para testes iniciais.

2. **Compilação**:  
   - Compile o projeto usando o sistema de build configurado (CMakeLists.txt).
   - O firmware gerado deverá estar no formato UF2 para ser carregado na BitDogLab.

3. **Testes no Simulador**:  
   - Utilize o simulador Wokwi para simular o circuito e verificar o funcionamento do código.
   - Faça testes interativos acionando os botões e observando a atualização da matriz de LEDs e o comportamento do LED de status.

4. **Testes na Placa Física (BitDogLab)**:  
   - Após simulação e testes no Wokwi, transfira o arquivo UF2 para a BitDogLab.
   - Coloque a placa no modo BOOTSEL conforme orientado e grave o firmware.

5. **Monitoramento Serial**:  
   - Utilize o software de terminal (ex.: PuTTY) para monitorar a saída serial e verificar as mensagens de depuração.

## Funcionamento Esperado

- Ao pressionar o **Botão A**:
  - Se o valor da variável `numero` for menor que 9, ele será incrementado em 1 e o padrão de LED correspondente será atualizado na matriz.
  - Se o valor máximo for alcançado, uma mensagem será impressa pedindo para pressionar o Botão B.

- Ao pressionar o **Botão B**:
  - Se o valor da variável `numero` for maior que 0, ele será decrementado em 1 e o padrão de LED correspondente será atualizado.
  - Se o valor mínimo for alcançado, uma mensagem será impressa pedindo para pressionar o Botão A.

- O LED de status pisca continuamente, indicando que o firmware está em execução.

## Estrutura do Projeto

- **main.c**: Código principal que inicializa o sistema, configura as interrupções e executa o loop de status.
- **inicia.h**: Biblioteca que contém a definição do buffer da matriz de LEDs, funções auxiliares (como `set_one_led()`) e a configuração do PIO para os LEDs WS2812.
- **iniciapino.h**: Biblioteca que realiza a inicialização dos pinos de entrada e saída (configuração dos botões e LED RGB).
- **Outros Arquivos**: Arquivos de configuração (ex.: CMakeLists.txt) e eventuais arquivos de suporte para o simulador Wokwi.

## Vídeo de Demonstração

Para demonstrar o funcionamento do projeto na BitDogLab, será produzido um vídeo com a seguinte indicação:

**(ESPAÇO PARA LINK)**

---

## Considerações Finais

Este projeto integra conceitos de interrupções, controle de GPIO, temporização e uso de periféricos endereçáveis (WS2812) para criar uma aplicação interativa que responde à entrada do usuário por meio de botões. A implementação foi feita utilizando o Pico SDK e foi testada tanto no simulador Wokwi quanto na Placa de Desenvolvimento BitDogLab.
