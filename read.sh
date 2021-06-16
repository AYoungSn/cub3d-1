# gcc -Wall -Werror -Wextra -fsanitize=address gnl/*.c config/*.c utils/*.c main.c -o parse_map;

gcc -Wall -Werror -Wextra -fsanitize=address gnl/*.c bonus/map_check_bonus.c bonus/map_bonus.c bonus/valid_check_bonus.c bonus/config_bonus.c bonus/parse_bonus.c utils/*.c config_main_bonus.c -o cub3D;

# echo "fail case"
# for ((i=1;i<=57;i++))
# do
# 	echo $i
# 	./cub3D ./maps/fail$i.cub
# done

# echo "success"
# for ((i=1;i<=12;i++))
# do
# 	echo $i
# 	./cub3D ./maps/test$i.cub
# done

# echo bonus
# for ((i=1;i<=2;i++))
# do
# 	echo $i
# 	./parse_map ./maps/bonus$i.cub
# done