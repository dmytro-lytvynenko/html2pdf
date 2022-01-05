git clone https://github.com/libharu/libharu.git
cd libharu
sh buildconf.sh
./configure
sudo make install
make clean
sudo ldconfig /usr/local/lib
echo ""
echo "You can find dll here:"
echo "cd /usr/local/lib"
echo ""