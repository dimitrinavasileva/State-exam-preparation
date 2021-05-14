#lang racket

;16.09.2020
(define (recommender pl)
  (lambda (track)
    ;(define (avgDuration artist) (/ (sum (map caddr (filter (lambda (p) (equal? artist (car p))) pl)))
    ;                                (length (filter (lambda (p) (equal? artist (car p)))))))
    (define (avgDuration artist) (let* ((artist-tracks (filter (lambda (p) (equal? artist (car p))) pl))
                                       (count-tracks (length artist-tracks))
                                       (total-duration (sum (map caddr artist-tracks))))
                                   (/ total-duration count-tracks)))
    (define option1 (let ((artist-tracks (filter (lambda (p) (equal? (car track) (car p))) pl)))
                      (filter (lambda (p) (> (caddr p) (caddr track))) artist-tracks)))
    
    (define option2 (filter (lambda (p) (> (avgDuration (car track)) (avgDuration (car p)))) pl))
    
    (if (not (null? option1))
        (cadar option1)
        (if (not (null? option2))
           (cadar (reverse option2))
           ;(if (not (null? (filter (lambda (p) (> (caddr p) (caddr track))) pl)))
           ;    (cadar (filter (lambda (p) (> (caddr p) (caddr track))) pl))
           ;    (cadr track))))
           (let ((longer-tracks (filter (lambda (p) (> (caddr p) (caddr track))) pl)))
             (if (not (null? longer-tracks))
                 (cadar longer-tracks)
                 (cadr track)))))
  ))



(define rf (recommender '(("Mozart" "The Marriage of Figaro Overture" 270)
                          ("Gershwin""Summertime" 300)
                          ("Queen" "Bohemian Rhapsody" 355)
                          ("Gershwin" "Rhapsody in Blue" 1100))))
(rf '("Mozart" "The Marriage of Figaro Overture" 270))
(rf '("Gershwin" "Summertime" 300))
(rf '("Gershwin" "Rhapsody in Blue" 1100))

;05.08.2020
(define (argMin f l) (foldr (lambda (current result) (if (< (f current) (f result)) current result))
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

;10.09.2019
(define db (list (cons "scheme" (list (cons "typing" "dynamic") (cons "evaluation" "strict")))
                 (cons "haskell" (list (cons "typing" "static"))) (cons "c++" (list))))

(define (evaluation lang)
  (case lang
    (("scheme") (list (cons "evaluation" "strict") (cons "macros" "true")))
    (("haskell") (list (cons "evaluation" "lazy"))) (("c++") (evaluation "scheme"))))

(define (purity lang) (if (eqv? lang "haskell") (list (cons "pure" "true")) (list)))



(define (addIfNew x l) (if (member x l) l (cons x l)))

(define (annotate db annotators)
  (map (lambda (item-labels-pair)
     (let ((item (car item-labels-pair)) (labels (cdr item-labels-pair)))
       (cons item (foldr addIfNew labels (apply append (map (lambda (annotator) (annotator item)) annotators)))))) db))
;(apply append '((1 2) (3 4)) - същото като flatten
;(append '(1 2) '(3 4))
;(apply + '(1 2 3))
;(+ 1 2 3)

;09.07.2019
(define (recomended basket bestFit products)
  (define (findPrice product)
    (cdr (assoc product products)))
  (define basketCost
    (apply + (map (lambda(p) (findPrice p)) baskewt)))
  (filter
   (lambda (product)
     (and (not (member product basket) (> (findPrice product) basketCost))))))

;Haskell
recommended :: [Int] -> (Int -> Int) -> [(Int,Double)] -> [Int]
recommended basket bestFit products =
filter
(\product -> 
   findPrice product <= basketCost && not (elem product basket))
  (map bestFit basket)
     where findPrice product =
             snd (head (filter (\p -> fst p == product) products))
           basketCost =
             sum (map findPrice basket)

;10.09.2018

;13.07.2018

;2017 не са давани задачи по Функционално програмиране

;09.09.2016

(define (member? x l)
  (cond ((null? l) #f)
        ((= x (car l)) #t)
        (else (member? x (cdr l)))))

(define (filterByElement x m)
  (filter (lambda (l) (member? x l)) m))

( filterByElement 2 '( (1 2 3) (2 3 4) (3 4 5) ) )

(apply + (map (lambda (l) (apply max l)) '((5 -2) (1 9) (6 -8))))

;10.09.2015

(define (merge l1 l2)
  (cond
      ((null? l1) l2)
      ((null? l2) l1)
      ((< (car l1) (car l2)) (cons (car l1) (merge (cdr l1) l2)))
      (else (cons (car l2) (merge l1 (cdr l2))))))

(merge `(1 3 5 7) `(2 2 6 10))

((lambda (l) (filter even? l)) `(1 2 3 4 5))

;11.09.2014
(define (remove ls elem)
 (cond ((null? ls) '())
       ((equal? (car ls) elem) (remove (cdr ls) elem))
       (else (cons (car ls) (remove (cdr ls) elem)))))

(define (permutations items)
 (if (null? items) '(())
     (apply append
        (map (lambda (element)
               (map (lambda (permutation)
                      (cons element permutation))
                    (permutations (remove items element))))
             items)
    )
  )
 )

; (permutations '(1 2 3)) ----> '((1 2 3) (1 3 2) (2 1 3) (2 3 1) (3 1 2) (3 2 1))

; 08.09.2010, state exam, problem 6

(define (generate-bin n)
    (define (toBin n)
        (if (<= n 1) 
            (cons n `())
            (cons (modulo n 2) (toBin (quotient n 2)))))

    (stream-cons (reverse (toBin n)) (generate-bin (+ n 1))))
    
;(writeln (stream->list (stream-take (generate-bin 0) 6)))
;(writeln (stream->list (stream-take (generate-bin 10) 7)))

; 15.07.2010, state exam, problem 6

(define (find-max l)
    (foldl (lambda (x acc) (+ x (* acc 10))) 0 (sort l >)))
    
;(writeln (find-max `()))
;(writeln (find-max `(1 2 3 0 1 4)))

; 10.09.2009, state exam, problem 8 

(define (compress-stream xs)
    (define (compress-helper xs cur count)
        (cond [(stream-empty? xs) (stream-cons (cons cur count) empty-stream)]
              [(and (eq? cur 0) (eq? (stream-first xs) cur)) (compress-helper (stream-rest xs) cur (+ count 1))]
              [(eq? cur 0) (stream-cons (cons cur count) (compress-helper (stream-rest xs) (stream-first xs) 1))]
              [else (stream-cons cur (compress-helper (stream-rest xs) (stream-first xs) 1))]))
                
    (cond [(stream-empty? xs) empty-stream]
          [else (compress-helper (stream-rest xs) (stream-first xs) 1)]))

(define (uncompress-stream xs)
    (define (repeat val count)
        (cond [(eq? count 0) empty-stream]
              [else (stream-cons val (repeat val (- count 1)))]))
    
    (cond [(stream-empty? xs) empty-stream]
          [(pair? (stream-first xs)) (stream-append (repeat (car (stream-first xs)) (cdr (stream-first xs))) (uncompress-stream (stream-rest xs)))]
          [else (stream-cons (stream-first xs) (uncompress-stream (stream-rest xs)))]))

    
;(writeln (stream->list (compress-stream (stream 0 0 0 1 0 0 7 3 0))))
;(writeln (stream->list (uncompress-stream (stream (cons 0 3) 1 (cons 0 2) 7 3 (cons 0 1)))))

; 15.07.2009, state exam, problem 7

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
        (cond [(eq? count 0) `()]
              [else (cons val (repeat val (- count 1)))]))
    
    (flatten (map (lambda (x) (repeat (car x) (cdr x))) xs)))

;(writeln (uncompress `((2 . 3) ("Stan" . 1) (7 . 2) (2 . 1))))

