uses
  GraphABC;
type
  TPoint = record
    X, Y, R : Integer;
  end;
  TPoints = array of TPoint;

procedure push(var V : TPoints; P : TPoint);
var
  n : Integer;
begin
  n := Length(V);
  SetLength(V, n + 1);
  v[n] := P;
end;

function Gen(W, H : Integer; min_side, max_side, K : Integer) : TPoints;
var
  PP : TPoints;
  P : Tpoint;
  n, errors, i : LongInt;
  f : Boolean;
begin
  while Length(PP) < K do 
  begin
    repeat 
      P.x := Random(W);
      P.y := Random(H);
      P.R := min_side + Random(max_side - min_side);
    until (P.x - P.R > 2) and (P.x + P.R < W - 2) and (P.y - P.R > 2) and (P.y + P.R < H - 2);
    n := Length(PP);
    f := true;
    
    for i := 0 to n-1 do
    begin
      if sqr(PP[i].x - P.x) + sqr(PP[i].y - P.y) <= sqr(PP[i].R + P.R + 1) then
      begin
        f := false;
        break;
      end;
    end;
    if f then push(PP, P) else errors += 1;
    if errors > K * 5000 then
    begin
      Gen := PP;
      exit;
    end;
  end;
  
  Gen := PP;
end;

function RotPoint(P : Point; C : Point; alpha : Integer) : Point;
var
  Q : Point;
begin
  Q.x := Round( (P.x  - C.x) * cos(alpha * pi / 180) - (P.y - C.y) * sin(alpha * pi / 180) + C.x );
  Q.y := Round( (P.x  - C.x) * sin(alpha * pi / 180) + (P.y - C.y) * cos(alpha * pi / 180) + C.y );
  RotPoint := Q;
end;

function RandBool : Boolean;
var
  a : Integer;
begin
  a := Random(2);
  if a = 0 then RandBool := False else  RandBool := True;
end;

procedure DrawRect(P : TPoint; is_square, is_colored, is_fill, is_border, is_rot, is_arcs, is_rand : Boolean);
var
  x0, y0, x1, y1, x2, y2 : Integer;
  alpha : Integer;
  a, b : Integer;
  C, C1 : Color;
  CC : array of Color = (ClRed, ClOrange, ClGreen, ClBlue, ClYellow, ClMagenta, ClBlack);
begin
  if is_rand then begin
    is_square := RandBool;    is_colored := RandBool;     is_fill := RandBool;
    is_border := RandBool;    is_rot := RandBool;    is_arcs := RandBool;
  end;
  alpha := 0;
  if is_rot then alpha := Random(360);
  if is_colored then C := CC[random(Length(CC))] else C := ClBlack;
  SetPenColor(C);
  if is_fill then begin
    if is_border then C1 := CC[random(Length(CC))] else C1 := C;
    SetBrushColor(C1);
  end;
  a := Round(P.r / sqrt(2) * (0.25 + Random));
  b := Round(sqrt(abs(sqr(P.r) - a * a)));
  if is_square then begin
    a := Round(P.r / sqrt(2));
    b := a;
  end;
  
  Coordinate.Angle := alpha;
  x0 := round(P.x * cos(alpha * pi / 180) + P.y * sin(alpha * pi / 180));
  y0 := round(-P.x * sin(alpha * pi / 180) + P.y * cos(alpha * pi / 180));
  
  x1 := x0 - a;
  y1 := y0 + b;
  x2 := x0 + a;
  y2 := y0 - b;          
  if is_arcs then RoundRect(x1, y1, x2, y2, 5 + random(10), 5 + random(10)) else Rectangle(x1, y1, x2, y2);
end;

procedure DrawTest(PP : TPoints; is_square, is_colored, is_fill, is_border, is_rot, is_arcs, is_rand : Boolean);
var
  n, i : Integer;
begin
  n := Length(PP);
  for i := 0 to n-1 do DrawRect(PP[i], is_square, is_colored, is_fill, is_border, is_rot, is_arcs, is_rand)
end;

function Int2Bool(a : Integer) : Boolean;
begin
  if a = 0 then Int2Bool := False else Int2Bool := True;
end;
  
var
  PP : TPoints;
  W, H, Rmin, Rmax, Count : Integer;
  N, k, i, id : Integer;
  b : array[1..7] of Integer;
  u : array[1..7] of Boolean;
  out, inp, S : string;
begin
    {---------
    W := 600; // ширина картинки
    H := 200; // висота картинки 
    Rmin := 20; // мінімальний розмір
    Rmax := 50; // максимальний розмір
    Count := 1050; // максимальна кількість
    u[1] := false; // is_square, // якщо true, то це квадрати
    u[2] := false; // is_colored, // якщо true, то буде кольорова границя
    u[3] := false; // is_fill, // якщо true, то буде кольорове заповнення
    u[4] := false; // is_border, // якщо true, то буде границя іншого кольору
    u[5] := true; // is_rot, // якщо true, то буде обертання на випадковий кут
    u[6] := true; // is_arcs // якщо true, то будуть заокруглені кути
    u[7] := true; // is_rand // всяке може бути :) - для кожного прямокутника всі параметри обираються випадково
    ---------}
    
    Assign(input, 'input.txt');
    Reset(input);
    ReadLn(N);
    ReadLn(S);
    for k := 1 to N do begin
      Read(id, W, H, Rmin, Rmax, Count);
      for i := 1 to 7 do begin Read(b[i]); u[i] := Int2Bool(b[i]); end;
      str(k, inp);
      if k < 10 then inp := '0' + inp;
      out := inp + '.out';
      inp := inp + '.png';
      
      SetWindowSize(W, H);
      SetPenColor(clBlack);
      SetBrushColor(clWhite);
      SetWindowCaption(inp);
      PP := Gen(W, H, Rmin, Rmax, Count); // W, H, Rmin, Rmax, Count
      Assign(output, out);
      ReWrite(output);
      WriteLn(Length(PP));
      Close(output);
      DrawTest(PP, u[1], u[2], u[3], u[4], u[5], u[6], u[7]); 
      SaveWindow(inp);
      Sleep(5000);
      ClearWindow;
    end;
    CloseWindow;
end.
