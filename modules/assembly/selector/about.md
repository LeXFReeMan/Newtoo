﻿# Парсеры CSS Селекторов  
Парсеры CSS селекторов читают строку справа налево и сравнивают селекторы с выбранным элементом. Если элемент соответствует всем селекторам, парсер возращает true, иначе false. Существуют также списки селекторов. Когда парсятся списки селекторов, достаточно, чтобы элемент соответствовал как миниум всем селекторам из одного пункта списка. Самих селекторов очень много.  
  
  
Представляем два парсера CSS селекторов:
- Токенный парсер (новинка)
- Экспресс парсер
# Токенный парсер
Токенный парсер селекторов разбивает строку на отрезки, которые затем превращает в токены, которые потом можно распарсить. Плюс данного парсера в том, что токены парсятся очень быстро. Достаточно один раз распрарсить строку с селекторами, чтобы потом очень быстро сравнивать её со всеми элементами страницы.
# Экспресс парсер
Этот парсер быстро парсит строку с селекторами, не превращая её в токены, ведь на это уходит довольно много времени. Такой парсер подойдет, чтобы быстро сравнить один или пару элементов, но для сравнения большого количества элементов не эффективен, для таких задач лучше использовать токенный парсер. Кроме того, экспресс парсер не расходует память, в отличии от токенного парсера, для которого надо хранить сами токены.
# Планы на будущее
Вместо экспресс парсера использовать токенный парсер для каскадирования CSS стилей
