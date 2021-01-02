gtk_dice_sources = [
  'main.c',
  'gtk_dice-window.c',
]

gtk_dice_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
]

gnome = import('gnome')

gtk_dice_sources += gnome.compile_resources('gtk_dice-resources',
  'gtk_dice.gresource.xml',
  c_name: 'gtk_dice'
)

executable('gtk-dice', gtk_dice_sources,
  dependencies: gtk_dice_deps,
  install: true,
)
