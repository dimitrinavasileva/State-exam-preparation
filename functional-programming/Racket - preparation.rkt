#lang racket

(define (revlex-less? a b)
  (cond ((= a 0) (> b 0))
        ((= b 0) #f)
        ((< (remainder a 10) (remainder b 10)) #t)
        ((> (remainder a 10) (remainder b 10)) #f)
        (else (revlex-less? (quotient a 10) (quotient b 10)))
  )
)
(writeln (revlex-less? 91 5)) ;true 91 is before 5
(writeln (revlex-less? 23 13)) ;false "23 is NOT before 13"

(define (number-valid? n)
  (cond ((< n 10) #t)
        ((= (remainder n 100) 0) #f) ;two consecutive zeros
        (else (number-valid? (quotient n 10)))
  )
)
(writeln (number-valid? 12003)) ; NOT valid
(writeln (number-valid? 1203)) ; valid

(define (ascending? n)
  (cond ((< n 10) #t)
        ((<= (remainder n 10) (remainder (quotient n 10) 10)) #f)
        (else (ascending? (quotient n 10)))
  )
)
(writeln (ascending? 1259)) ;Yes
(writeln (ascending? 923))  ;No


;Sept 2020
(define (recommender pl)
  (lambda (track)
  (define (avgDuration artist) 
     (let* ((artist-tracks (filter (lambda (p) (equal? (car p) artist)) pl))
            (track-duration (map last artist-tracks))
            (count-tracks (length artist-tracks)))
	   (/ (apply + track-duration) count-tracks)))
  (define option1
    (let ((artist-tracks (filter (lambda (p) (equal? (car track) (car p))) pl)))
         (filter (lambda (p) (> (last p) (last track))) artist-tracks)))
  (define option2 (filter (lambda (p) (> (avgDuration (car track)) (avgDuration (car p)))) pl))
  (if (not (null? option1))
      (cadar option1)
      (if (not (null? option2))
          (cadar (reverse option2))
          (let ((longer-tracks (filter (lambda (p) (> (last p) (last track))) pl)))
               (if (not (null? longer-tracks))
                   (cadar longer-tracks)
                   (cadr track)))))))

(define rf (recommender '(("Mozart" "The Marriage of Figaro Overture" 270)
                           ("Gershwin""Summertime" 300)
                           ("Queen" "Bohemian Rhapsody" 355)
                           ("Gershwin" "Rhapsody in Blue" 1100))))
(rf '("Mozart" "The Marriage of Figaro Overture" 270))
(rf '("Gershwin" "Summertime" 300))
(rf '("Gershwin" "Rhapsody in Blue" 1100))

;July 2020
(define (argMin f l) (foldr (lambda (current result)
                              (if (< (f current) (f result))
                                  current
                                  result)
                             )
                             (car l)
                             l))

(define (maxSlope track)
  ;(foldr max (car smth) (cdr smth))
  (apply max (map (lambda (t1 t2) (abs (/ (- (cdr t1) (cdr t2)) (- (car t1) (car t2)))))
        (reverse (cdr track)) (cdr (reverse track)))))

;абсолютната стойностна отношението на разликата във височините им и дължината на изминатия път между тях.
; долу са примерни (reverse (cdr track)) и (cdr (reverse track)), които map минава поелементно
;'((600 . 950) (300 . 905) (200 . 925) (100 . 910))
;'((300 . 905) (200 . 925) (100 . 910) (0 . 900))

(define (easiestTrackUnder maxLen tracks)
  (argMin maxSlope (filter (lambda (track) (< (caar (reverse track)) maxLen)) tracks)))


(define tracks '(((0 . 900) (100 . 910) (200 . 925) (300 . 905) (600 . 950))
                 ((0 . 1300) (100 . 1305) (500 . 1340) (800 . 1360) (1000 . 1320))
                 ((0 . 800) (200 . 830) (300 . 845) (600 . 880) (800 . 830))))

(maxSlope (car tracks))
(easiestTrackUnder 800 tracks)

;Sept 2019
(define (addIfNew x l) 
  (if (not (member x l))
      (cons x l)
      l
      )
)
(define (annotate db annotators)
  (map (lambda (item-labels-pair)
     (let ((item (car item-labels-pair)) (labels (cdr item-labels-pair)))
          (cons item (foldr addIfNew labels (apply append (map (lambda (annotator) (annotator item))
                                                               annotators))))
     )
   )
db))

(define db (list (cons "scheme" (list (cons "typing" "dynamic") (cons "evaluation" "strict")))(cons "haskell" (list (cons "typing" "static"))) (cons "c++" (list))))
(define (evaluation lang)(case lang (("scheme")  (list (cons "evaluation" "strict") (cons "macros" "true")))(("haskell") (list (cons "evaluation" "lazy"))) (("c++") (evaluation "scheme"))))
(define (purity lang) (if (eqv? lang "haskell") (list (cons "pure" "true")) (list)))
;(annotate db (list evaluation purity)) --> (("scheme" ("macros" . "true") ("typing" . "dynamic") ("evaluation" . "strict"))("haskell" ("evaluation" . "lazy") ("pure" . "true") ("typing" . "static"))("c++" ("evaluation" . "strict") ("macros" . "true")))

;July 2019
(define products '((45126 1) (14523 20)(47823 43)))
(define basket '(45126 14523 47823))

;(findPrice 45126) ----> '(1) ---> Връща списък, за да не се налага после да flatt-ваме ще използваме second вместо cdr
(define (findPrice product) 
    (second (assoc product products)) 
    )

;(map (lambda (p) (findPrice p)) basket) ---> basketCost '((1) (20) (43)) ---> flatten then apply +
(define basketCost
  (apply + (map (lambda (p) (findPrice p)) basket)))

(define (recommended basket bestFit products)
  (define (findPrice product) 
    (cdr (assoc product products))
    )

  (define basketCost
  (apply + (flatten (map (lambda (p) (findPrice p)) basket))))

  (filter
   (lambda (product)
     (and (not (member product basket))
          (< (findPrice product) basketCost)))
   (map bestFit basket))
)

;FP tasks 2018

;NO FP tasks 2017

;Sept 2016

(define (filterByElement x m)
  (filter (lambda (p) (member x p)) m))

;(apply + (map (lambda (l) (apply max l) ) '((5 -2) (1 9) (6 -8) ))) --> 20

;July 2016 ++
;(map (lambda (x) (append (list x) x) ) '( (1 2) (3 4) ) ) --> '(((1 2) 1 2) ((3 4) 3 4))
;(map (lambda (f) (map (lambda (x) (f 5 x)) '(1 2 3) )) (list + -­ *)) --> '((6 7 8) (4 3 2) (5 10 15))
;(apply list (list (quote +) (quote 5) 8) ) --> '(+ 5 8)

;Sept 2015
(define (merge l1 l2)
  (cond ((null? l1) l2)
        ((null? l2) l1)
        ((< (car l1) (car l2)) (cons (car l1)(merge (cdr l1) l2)))
        (else (cons (car l1)(merge l1 (cdr l2))))))

((lambda (p) (filter even? p)) '(1 2 3 4))

;(map (lambda (p) (remove (second p) p)) (apply append '( ( (1 2) ) ( (3 4) ) ))) ---> '((1) (3))
;(map (lambda (p) (list (car p))) (apply append '( ( (1 2) ) ( (3 4) ) ))) ----> '((1) (3))
;(map (lambda (p) (list (car p))) (apply append '( ( (1 . 2) ) ( (3 . 4) ) ))) ---> '((1) (3))
;(map (lambda (p) (list (cdr p))) (apply append '( ( (1 . 2) ) ( (3 . 4) ) ))) ---> '((2) (4))

;July 2015
;(map(car (list (lambda (couple) (+ (car couple) (cdr couple))))) (apply append '( ( (1 . 2) ) ( (3 . 4) ) ) )) -------> '(3 7)

;(cons 1 '(2)) --> '(1 2)
;(map (lambda (x) (cons x (list x)))'(1 2 3 4 5)) ---> '((1 1) (2 2) (3 3) (4 4) (5 5))

;(map (lambda (pred) (filter pred '(1 2 3 4 5))) (list even? odd?)) ---> '((2 4) (1 3 5))

;Sept 2014
;(permutations'(123)) → ((123)(132)(213)(231)(312)(321))

;July 2014 --> Too math

;2010 ---> Streams

;Sept 2009 ---> Streams
;July 2009
;(2  2  2  Stan  7  7  2)
;After compression ---> ((2 . 3) (Stan . 1) (7 . 2) (2 . 1))
(define (compress xs)
    (define (compress-tail xs res cur count)
        (cond [(null? xs) (cons (cons cur count) res)]
              [(eq? (car xs) cur) (compress-tail (cdr xs) res cur (+ count 1))]
              [else (compress-tail (cdr xs) (cons (cons cur count) res) (car xs) 1)]))
                
    (cond [(null? xs) `()]
          [else (reverse (compress-tail (cdr xs) `() (car xs) 1))]))

;(writeln (compress `(2 2 2 "Stan" 7 7 2)))

(define (uncompress xs)
    (define (repeat val count)
        (cond [(equal? count 0) `()]
              [else (cons val (repeat val (- count 1)))]))
    
    (flatten (map (lambda (x) (repeat (car x) (cdr x))) xs)))

;(writeln (uncompress `((2 . 3) ("Stan" . 1) (7 . 2) (2 . 1))))

;March 2009
;(count-sub '(1 1) '(1 1 1 2 1 1))
(define (count-sub l1 l2)
  (cond ((> (length l1) (length l2)) 0)
        ((equal? (take l2 (length l1)) l1) (+ 1 (count-sub l1 (cdr l2))))
        (else (count-sub l1 (cdr l2)))))

;TESTS

(define (remove-duplicates l)
  (cond ((null? l) '())
        ((member (car l) (cdr l)) (remove-duplicates (cdr l)))
        (else (cons (car l) (remove-duplicates (cdr l))))))

(define (fact n)
 (letrec ([fact-iter (lambda (arg res)
                       (if (= arg 0)
                           res
                           (fact-iter (- arg 1) (* arg res))))])
 (fact-iter n 1)))

(define (lookup key a-list)
 (cond [(null? a-list) #f]
       [(equal? (caar a-list) key) (car a-list)]
       [else (lookup key (cdr a-list))]))

(define (rem-assoc key a-list)
 (cond [(null? a-list) '()]
       [(eq? key (caar a-list)) (cdr a-list)]
       [else (cons (car a-list)(rem-assoc key (cdr a-list)))]))