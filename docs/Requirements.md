# Requisitos de Hardware
* O sistema deverá ter saídas para controles de dispositivos, exemplo relés ou chave estática.
* O sistema deverá ter uma interface de entrada para realizar leitura de RFID (spi)
* O sistema deverá ter uma interface para interagir com o usuário via LCD
* O sistema deverá ter um teclado para inserir senha previamente cadastrada

# Requisitos de Software
* O sistema deverá registrar todos as leituras feitas pelo RFID ou via teclado, guardando o número do usuário e a 
data que ocorreu o evento.
* O sistema deverá emitir um relatório no formato .cvs para geração de gráfico de acesso via Excel/Br Calc
* O sistema deverá emitir um relatório no formato .txt para auditoria de usuários cadastrados
* O sistema deverá permitir o cadastro de um novo usuário 
* O sistema deverá permitir apagar um usuário cadastrado
* O sistema deverá permitir editar um usuário cadastrado

# Requisitos de conexão
* O sistema deverá se comunicar com dispositivos via MQTT
