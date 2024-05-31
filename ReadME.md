# N nesikertančių karalienių uždavinys trikampėje N dydžio lentoje

Įvedus N reikšmę, programa randa kiek daugiausiai galime pastatyti karalienių į N dydžio lentą, kad jos nesikirstų

Archyve taip pat yra straipsnis, kuriame įrodoma, kad N dydžio trikampėje lentoje galime išdėstyti daugiausia [2N+1] karalienių ir aprašyti būdai, kaip tai padaryti, tačiau programos sprendime straipsnis nenaudojamas, programa yra parašyta "brute-force" būdu, tikrinanti kiekvieną galima išdėstymą naudojant rekursiją su grįžimu.

Taip pat, sprendimas nėra efektyvus.

Alternatyvus ir daug efektyvesnis sprendimo būdas būtų sudaryti 2 masyvus: vieną kiekvienam įstrižainės tipui, ir taip tikrinti, kur galime padėti karalienę. Šis sprendimo būdas "rankiniu" būdu pakeičia kiekvieną trikampio poziciją, pradedant 0 ir +1 jei pozicija "atakuojama".

## Failai

- **Go.cmd** - automatizuoja testavimą (t.y. nueina į direktoriją, priklausant nuo kompiuterio, ir paleidžia "make")
- **Makefile** - kompiliuoja ir suriša failus testavimui
- **LFF** - laiko fiksavimo forma
- **max_queens.c** - .c failas sprendžiantis uždavinį
