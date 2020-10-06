sudo apt update && 
sudo apt install -y   \
    libsdl2-dev       \
    libpng-dev        \
    build-essential   \
    cmake

# create oXu dir the user's .config
user_config_oXu_dir=/home/$USER/.config/oXu

mkdir build $user_config_oXu_dir $user_config_oXu_dir/songs $user_config_oXu_dir/skins
cp -r res $user_config_oXu_dir 

echo Done!
