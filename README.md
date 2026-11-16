# Mars Kolonisi Yaşam Destek Simülatörü (C ile Metin Tabanlı Oyun Geliştirme)

## Proje Hakkında
Bu proje, C programlama dilinin temel yapıları kullanılarak geliştirilmiş metin tabanlı bir **Mars Kolonisi Yaşam Destek Simülatörü**'dür. Oyuncu, Mars'taki bir araştırma istasyonunda mahsur kalan tek bir mühendisi yönetir ve kurtarma ekibi gelene kadar **15 gün** boyunca hayatta kalmaya çalışır. 

Proje; sağlık, enerji, oksijen, su, yedek parça, modül hasarı ve gün/tur sayacını takip eden kapsamlı bir durum yönetimi altyapısına sahiptir.

- **Geliştirici:** Şafak Balcı
- **Öğrenci Numarası:** 1260505006
- **Ders:** Algoritma ve Programlama

---

## Özellikler ve Kullanılan C Yapıları

### 1. Komut Sistemi ve Switch-Case Yapısı
Oyuncu, konsol üzerinden tek karakterli komutlar girerek istasyonu yönetir. Komutlar büyük/küçük harf duyarsızdır (örn. `g` ve `G` aynı işlevi yapar); bu durum `switch-case` yapısında **fall-through** mekanizması ile sağlanmıştır. Tanımsız komutlar süre (tur) harcamaz ve kullanıcıyı uyarır.

Zorluk seviyesi seçimi de ayrı bir `switch-case` bloğu ile gerçekleştirilmekte olup, geçersiz girişlerde seçim yinelenmektedir.

### 2. Aritmetik ve Mantıksal İşlem Mekanizmaları
- **Keşif (G):** Enerji (-15) ve oksijen (-10) tüketir. Su veya yedek parça bulma ihtimali mantıksal operatörler (`&&`, `||`) ve `rand() % 100` ile değerlendirilir. Yüksek hasar veya düşük zar durumlarında karakter yaralanabilir.
- **Oksijen Üretimi (O):** 2 birim su, 3 birim oksijene dönüştürülür. Mod operatörü (`%`) kullanılarak tek/çift su miktarlarının artıkları hesaplanır.
- **Tamir (T):** Yedek parça tüketerek modül hasarını azaltır. Hasar seviyesi `if-else if-else` zinciri ile kademelendirilmiştir (Hafif: 0-30, Orta: 31-70, Ağır: 71-100).
- **Dinlenme (U):** Enerji ve sağlık kazanımı sağlar. İç içe `if` koşulu ile oksijen 20'nin altındaysa sağlık artışı yerine sağlık kaybı yaşanır.
- **Durum Raporu (D):** Kritik değerler (oksijen < 25, sağlık < 30, hasar > 70) için özel uyarılar üretir. Tüm değerler güvenliyse `&&` ile birleştirilmiş tek koşulla `"TÜM SİSTEMLER NORMAL"` mesajı yazdırır.
- **Kaynak ve Sınır Kontrolleri:** Tüm temel değişkenler (sağlık, enerji, oksijen, modül hasarı) hiçbir zaman 0'ın altına düşmez ve 100'ü aşmaz. Yetersiz enerji durumunda ilgili komut çalıştırılmaz.

### 3. Döngü Yapıları (FOR ve DO-WHILE)
- **FOR Döngüsü - Kum Fırtınası Simülasyonu (K):** Zorluk seviyesine göre belirlenen tur sayısı boyunca (Kolay: 3, Normal: 5, Zor: 7 tur) çalışır. Her turda rastgele olaylar üretilir. Çift numaralı turlarda mod operatörü (`% 2 == 0`) ile rüzgar şiddetlenerek hasar iki katına çıkar. Hava kilidi mühürlüyse oksijen sızıntısı `continue` ile atlanır; kritik can/oksijen düşüşlerinde döngü `break` ile sonlandırılır.
- **DO-WHILE Döngüsü - Hava Kilidi Şifresi (H):** Gün sayısından aritmetik olarak türetilen büyük harfli şifreyi (`sifre = 'A' + (gun % 26)`) bulmak için 3 deneme hakkı sunar. Yanlış denemelerde enerji azalır ve "ileri/geri git" ipuçları verilir. Başarılı girişte kilit mühürlenir (`kilitMuhurlu = 1`), başarısızlıkta modül hasarı artar.

### 4. Zaman Akışı ve Oyun Sonu Skoru
- Her geçerli komut tur sayacını 1 artırır. Her 3 turda bir (`tur % 3 == 0`) yeni gün başlar; gün başında oksijen 8 azalır ve hasar 70'in üzerindeyse ek sağlık kaybı oluşur.
- **Oyun Sonu:** Sağlık veya oksijen 0 olursa oyun kaybedilir; 15. gün tamamlanırsa kurtarma ekibiyle oyun kazanılır.
- **Puan Formülü:** 
  $$\text{Puan} = (\text{gun} \times 100) + \text{saglik} + \text{oksijen} - \text{modulHasari}$$

---

## Komut Özeti

| Komut | Açıklama |
| :---: | :--- |
| **G / g** | Keşif görevi (Enerji ve oksijen harcar, su/yedek parça arar) |
| **O / o** | Oksijen üretimi (Su dönüştürerek oksijen üretir) |
| **T / t** | Modül tamiri (Yedek parça harcayarak hasarı düşürür) |
| **D / d** | Durum raporu (Mevcut istasyon ve sağlık durumunu gösterir) |
| **U / u** | Uyu / Dinlen (Enerji ve sağlık yeniler) |
| **K / k** | Kum fırtınası simülasyonu (FOR döngüsü ile fırtına yönetimi) |
| **H / h** | Hava kilidi şifre doğrulaması (DO-WHILE ile şifre çözme) |
| **Q / q** | Oyundan çıkış |

---

## Derleme ve Çalıştırma

Projeyi derlemek ve çalıştırmak için terminal üzerinde GCC (GNU Compiler Collection) kullanabilirsiniz:

```bash
# Projeyi derleme
gcc -o mars_sim main.c

# Simülasyonu başlatma
./mars_sim
```

## Lisans ve İletişim
Bu proje akademik bir ödev olarak geliştirilmiştir. Tüm hakları saklıdır.
