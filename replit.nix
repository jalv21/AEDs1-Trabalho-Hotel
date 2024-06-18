{ pkgs }:

let
  Process = pkgs.stdenv.mkDerivation {
    name = "Process";
    src = ./codigo;

    buildInputs = [ pkgs.gcc ];  # Apenas gcc é necessário para compilar

    buildPhase = ''
      gcc -c Process.c -o Process.o
      ar rcs libProcess.a Process.o
    '';

    installPhase = ''
      mkdir -p $out/lib $out/include
      cp libProcess.a $out/lib/
      cp Process.h $out/include/
    '';
  };

  Main = pkgs.stdenv.mkDerivation {
    name = "Main";
    src = ./codigo;

    buildInputs = [ pkgs.gcc Process ];  # Inclui Process como dependência

    buildPhase = ''
      gcc -I${Process}/include main.c -L${Process}/lib -lProcess -o main
    '';

    installPhase = ''
      mkdir -p $out/bin
      cp main $out/bin/
    '';
  };

in
{
  exports = {
    default = Main;  # Exporta a derivação Main como padrão
  };

  deps = [
    Process
    Main
  ];
}
