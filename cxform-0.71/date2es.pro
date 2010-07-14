;+
; NAME:
;   date2es
;
; PURPOSE:
;   Function to convert a standard calendar date into ephemeris seconds before
;   or after J2000.  Similar to Ephemeris Time/TDT, but disregards leap seconds
;   introduced in 1972.
;
; CALLING SEQUENCE:
;   es = date2es(month,day,year)
;     OR
;   es = date2es(month,day,year,hour,minute,second)
;
; INPUTS:
;   month, day, year: desired month, day, and year to convert
;      (MM,    DD,  YYYY)
;
;   Note that arrays are permitted, provided they're all the same length
;
; OPTIONAL INPUTS:
;   hour, minute, second: if included, the desired hour, minute, and second
;     of the specified day
;
; OUTPUTS:
;   es: The number of ephemeris seconds with respect to J2000, January 1,
;     2000 12:00:00, stored as a long integer.  An array of times are
;     returned if an array is used as input.
;
;   returns -1 if an error has occurred
;
; EXAMPLE:
;   ; Get the number of ephemeris seconds at 10/15/1987, 14:05:00 UTC
;   es = date2es(10,15,1987,14,05,00)
;
; RESTRICTIONS / NOTES:
;   This routine is a quick replacement for the SPICE library function
;   STR2ET.  Another routine, date2et is available that does take leap
;   seconds into account.
;
;   Note that this routine does not check for out-of-range input errors,
;   so unpredictable results may occur (GIGO).
;
;   Also note that this routine needs to be tested for complete accuracy
;   for use with Ryan Boller's CXFORM package.
;
;       For more info, see page 4 of
;     http://www.sp.ph.ic.ac.uk/~nach/PSG/joyce_venice.pdf
;
; MODIFICATION HISTORY:
;   2003/09/22: Ryan Boller (Ryan.A.Boller@nasa.gov) - Initial version
;   2003/09/25: Ryan Boller - Added array input capability
;   2004/01/16: Ryan Boller - Updated documentation to include differences
;          between ET & ES
;
;-

function date2es, mon, day, year, hr, minute, sec
    ; Check for correct number of input parameters
    if ((n_params() ne 3) and (n_params() ne 6)) then begin
       print, "Incorrect number of parameters.  Usage:"
       print, "     et = date2es(month,day,year)"
       print, "              or"
       print, "     et = date2es(month,day,year,hour,minute,second)"
       return, -1
    endif

    ; Get number of input elements
    nElem = n_elements(year)

    ; Initialize hr/min/sec if none provided
    if (n_elements(hr) lt 1) then begin
       hr =  lonarr(nElem)
       minute = lonarr(nElem)
       sec = lonarr(nElem)
    endif

    ; Check preconditions
    if ((n_elements(mon) ne n_elements(day))  or  $
        (n_elements(mon) ne n_elements(year)) or  $
        (n_elements(mon) ne n_elements(hr))   or  $
        (n_elements(mon) ne n_elements(minute))  or  $
            (n_elements(mon) ne n_elements(sec))) then begin
       print, "Error:  All input arrays must have the same length"
       return, -1
    endif

    ; Allocate arrays
    JD =    dblarr(nElem, /NOZERO)
    secFromJ2000 =     lonarr(nElem, /NOZERO)
    ;DELTA_AT =     lonarr(nElem, /NOZERO)
    ;TAI =      lonarr(nElem, /NOZERO)
    ;TDT =      lonarr(nElem, /NOZERO)

    ; Get Julian Day
    for i=0, (nElem-1) do begin
       JD[i] = DOUBLE(Julday(mon[i],day[i],year[i],0,0,0))
    endfor

    ; Add in hours and seconds separately, as Julday is imprecise
    JD[*] = JD[*] + hr[*]/24d + minute[*]/1440d + sec[*]/86400d


    ; Calculate # seconds from J2000 relative to given time in UTC
    secFromJ2000[*] = ROUND((JD[*] - 2451545l) * 86400l)


    ; Return a scalar (secFromJ2000[0]) if scalar arguments were provided
    if (n_elements(secFromJ2000) eq 1) then return, secFromJ2000[0]   $
    else return, secFromJ2000

END