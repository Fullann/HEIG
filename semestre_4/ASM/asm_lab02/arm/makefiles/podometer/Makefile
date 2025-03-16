# Outils de compilation
CC         = arm-linux-gnueabihf-gcc
AS         = arm-linux-gnueabihf-gcc
AR         = arm-linux-gnueabihf-ar
OBJCOPY    = arm-linux-gnueabihf-objcopy

# Options de compilation et d'édition de liens
CFLAGS     = -fno-builtin -I../../../u-boot/include -I../../../u-boot/arch/arm/include -D_KERNEL_ -marm -g
LDFLAGS    = -T asm.lds -marm -g

# Sources C de l'exécutable podometer
C_SRCS     = podometer.c system.c ctrl_led.c uart.c transfer.c stubs.c

# Source assembleur de démarrage
S_SRCS     = crt0.S

# Sources pour la librairie libsensio.a
LIB_SRCS   = gpio.c imu.c

# Fichiers objets correspondants
C_OBJS     = $(C_SRCS:.c=.o)
S_OBJS     = $(S_SRCS:.S=.o)
LIB_OBJS   = $(LIB_SRCS:.c=.o)

# Nom de la librairie
LIB        = libsensio.a

# Nom de l'exécutable et de l'image binaire
TARGET     = podometer
BIN        = podometer.bin

# Cibles spéciales
.PHONY: all clean checklib

# Cible par défaut : construire l'exécutable et le .bin
all: $(TARGET) $(BIN)

# Edition de liens de l'exécutable
$(TARGET): $(C_OBJS) $(S_OBJS) $(LIB)
	$(CC) $(C_OBJS) $(S_OBJS) -L. -lsensio $(LDFLAGS) -o $(TARGET)

# Génération du fichier binaire via objcopy
$(BIN): $(TARGET)
	$(OBJCOPY) -O binary $(TARGET) $(BIN)

# Règle de compilation des fichiers C
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de compilation des fichiers assembleur (.S)
%.o: %.S
	$(AS) $(CFLAGS) -c $< -o $@

# Création de la librairie statique libsensio.a
$(LIB): $(LIB_OBJS)
	$(AR) rcs $(LIB) $(LIB_OBJS)

# Cible checklib pour vérifier la librairie
checklib: $(LIB)
	@echo "La librairie $(LIB) est à jour."

# Nettoyage des fichiers générés
clean:
	rm -f $(C_OBJS) $(S_OBJS) $(LIB_OBJS) $(LIB) $(TARGET) $(BIN)