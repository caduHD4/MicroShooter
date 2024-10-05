# Nome do compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -g

# Arquivo executável
TARGET = PlayerTest

# Arquivo de código fonte
SRC = PlayerTest.cpp

# Regra padrão para compilar o projeto
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Limpar os arquivos de compilação
clean:
	rm -f $(TARGET)
