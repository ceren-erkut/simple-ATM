library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity password_entry is
Port (a : in std_logic_vector(3 downto 0);
  clk : in std_logic;
  btnC : in std_logic;
  start : out std_logic;
  LED : out std_logic_vector(4 downto 0);
  JA : out  std_logic_vector (3 downto 0) );
end password_entry;

architecture Behavioral of password_entry is

begin

   start <=  btnC;
   LED(4) <= btnC;

   JA <= a;
   LED (3 downto 0) <= a;
   
end Behavioral;
