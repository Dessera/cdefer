{ pkgs, ... }:
ccenv:
let
  target =
    {
      stdenv,
      lib,

      # Build tools
      meson,
      ninja,
      pkg-config,
    }:
    stdenv.mkDerivation {
      name = "tocli";
      src = lib.cleanSource ../.;

      nativeBuildInputs = [
        meson
        ninja
        pkg-config
      ];
    };
in
{
  default = pkgs.callPackage target {
    stdenv = ccenv;
  };
}
