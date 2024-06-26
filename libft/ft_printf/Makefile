SRCS = ft_printf.c \
	   ft_putadress.c \
	   ft_putchar.c \
	   ft_puthexa_lower.c \
	   ft_puthexa_upper.c \
	   ft_putnbr.c \
	   ft_putstr.c \
	   ft_putunbr.c \

OBJS = $(SRCS:.c=.o)

LIB = libftft_printf.a

CPPFLAGS = -I..
CFLAGS	 = -Wall -Werror -Wextra

$(LIB):	$(OBJS)
		$(AR) crs $(LIB) $(OBJS)

all: 	$(LIB)

clean:
		rm -f $(OBJS)

fclean:	clean;
		rm -f $(LIB)

re:	fclean all

.PHONY: all clean fclean re
