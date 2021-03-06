/*
*******************************************************************************
*   Copyright (C) 1996-2008, International Business Machines
*   Corporation and others.  All Rights Reserved.
*******************************************************************************
* Modification History:
*
*   Date        Name        Description
*   06/24/99    helena      Integrated Alan's NF enhancements and Java2 bug fixes
*******************************************************************************
*/

#include "unicode/utypes.h"

#if !UCONFIG_NO_FORMATTING

#include "unicode/unum.h"

#include "unicode/uloc.h"
#include "unicode/numfmt.h"
#include "unicode/decimfmt.h"
#include "unicode/rbnf.h"
#include "unicode/ustring.h"
#include "unicode/fmtable.h"
#include "unicode/dcfmtsym.h"
#include "unicode/curramt.h"
#include "uassert.h"
#include "cpputils.h"


U_NAMESPACE_USE


U_CAPI UNumberFormat* U_EXPORT2
unum_open(  UNumberFormatStyle    style,  
            const    UChar*    pattern,
            int32_t            patternLength,
            const    char*     locale,
            UParseError*       parseErr,
            UErrorCode*        status)
{

    if(U_FAILURE(*status))
    {
        return 0;
    }

    UNumberFormat *retVal = 0;

    switch(style) {
    case UNUM_DECIMAL:
        if(locale == 0)
            retVal = (UNumberFormat*)NumberFormat::createInstance(*status);
        else
            retVal = (UNumberFormat*)NumberFormat::createInstance(Locale(locale),
            *status);
        break;

    case UNUM_CURRENCY:
        if(locale == 0)
            retVal = (UNumberFormat*)NumberFormat::createCurrencyInstance(*status);
        else
            retVal = (UNumberFormat*)NumberFormat::createCurrencyInstance(Locale(locale),
            *status);
        break;

    case UNUM_PERCENT:
        if(locale == 0)
            retVal = (UNumberFormat*)NumberFormat::createPercentInstance(*status);
        else
            retVal = (UNumberFormat*)NumberFormat::createPercentInstance(Locale(locale),
            *status);
        break;

    case UNUM_SCIENTIFIC:
        if(locale == 0)
            retVal = (UNumberFormat*)NumberFormat::createScientificInstance(*status);
        else
            retVal = (UNumberFormat*)NumberFormat::createScientificInstance(Locale(locale),
            *status);
        break;

    case UNUM_PATTERN_DECIMAL: {
        UParseError tErr;
        /* UnicodeString can handle the case when patternLength = -1. */
        const UnicodeString pat(pattern, patternLength);
        DecimalFormatSymbols *syms = 0;

        if(parseErr==NULL){
            parseErr = &tErr;
        }

        if(locale == 0)
            syms = new DecimalFormatSymbols(*status);
        else
            syms = new DecimalFormatSymbols(Locale(locale), *status);

        if(syms == 0) {
            *status = U_MEMORY_ALLOCATION_ERROR;
            return 0;
        }

        retVal = (UNumberFormat*)new DecimalFormat(pat, syms, *parseErr, *status);
        if(retVal == 0) {
            delete syms;
        }
                               } break;

#if U_HAVE_RBNF
    case UNUM_PATTERN_RULEBASED: {
        UParseError tErr;
        /* UnicodeString can handle the case when patternLength = -1. */
        const UnicodeString pat(pattern, patternLength);
        
        if(parseErr==NULL){
            parseErr = &tErr;
        }
        
        retVal = (UNumberFormat*)new RuleBasedNumberFormat(pat, Locale(locale), *parseErr, *status);
    } break;

    case UNUM_SPELLOUT:
        retVal = (UNumberFormat*)new RuleBasedNumberFormat(URBNF_SPELLOUT, Locale(locale), *status);
        break;

    case UNUM_ORDINAL:
        retVal = (UNumberFormat*)new RuleBasedNumberFormat(URBNF_ORDINAL, Locale(locale), *status);
        break;

    case UNUM_DURATION:
        retVal = (UNumberFormat*)new RuleBasedNumberFormat(URBNF_DURATION, Locale(locale), *status);
        break;
#endif

    default:
        *status = U_UNSUPPORTED_ERROR;
        return 0;
    }

    if(retVal == 0 && U_SUCCESS(*status)) {
        *status = U_MEMORY_ALLOCATION_ERROR;
    }

    return retVal;
}

U_CAPI void U_EXPORT2
unum_close(UNumberFormat* fmt)
{
    delete (NumberFormat*) fmt;
}

U_CAPI UNumberFormat* U_EXPORT2
unum_clone(const UNumberFormat *fmt,
       UErrorCode *status)
{
    if(U_FAILURE(*status))
        return 0;
    
    Format *res = 0;
    if (((const NumberFormat*)fmt)->getDynamicClassID() == DecimalFormat::getStaticClassID()) {
        res = ((const DecimalFormat*)fmt)->clone();
    } else {
        U_ASSERT(((const NumberFormat*)fmt)->getDynamicClassID() == RuleBasedNumberFormat::getStaticClassID());
        res = ((const RuleBasedNumberFormat*)fmt)->clone();
    }

    if(res == 0) {
        *status = U_MEMORY_ALLOCATION_ERROR;
        return 0;
    }
    
    return (UNumberFormat*) res;
}

U_CAPI int32_t U_EXPORT2
unum_format(    const    UNumberFormat*    fmt,
        int32_t           number,
        UChar*            result,
        int32_t           resultLength,
        UFieldPosition    *pos,
        UErrorCode*       status)
{
        return unum_formatInt64(fmt, number, result, resultLength, pos, status);
}

U_CAPI int32_t U_EXPORT2
unum_formatInt64(const UNumberFormat* fmt,
        int64_t         number,
        UChar*          result,
        int32_t         resultLength,
        UFieldPosition *pos,
        UErrorCode*     status)
{
    if(U_FAILURE(*status))
        return -1;
    
    UnicodeString res;
    if(!(result==NULL && resultLength==0)) {
        // NULL destination for pure preflighting: empty dummy string
        // otherwise, alias the destination buffer
        res.setTo(result, 0, resultLength);
    }
    
    FieldPosition fp;
    
    if(pos != 0)
        fp.setField(pos->field);
    
    ((const NumberFormat*)fmt)->format(number, res, fp);
    
    if(pos != 0) {
        pos->beginIndex = fp.getBeginIndex();
        pos->endIndex = fp.getEndIndex();
    }
    
    return res.extract(result, resultLength, *status);
}

U_CAPI int32_t U_EXPORT2
unum_formatDouble(    const    UNumberFormat*  fmt,
            double          number,
            UChar*          result,
            int32_t         resultLength,
            UFieldPosition  *pos, /* 0 if ignore */
            UErrorCode*     status)
{
 
  if(U_FAILURE(*status)) return -1;

  UnicodeString res;
  if(!(result==NULL && resultLength==0)) {
    // NULL destination for pure preflighting: empty dummy string
    // otherwise, alias the destination buffer
    res.setTo(result, 0, resultLength);
  }

  FieldPosition fp;
  
  if(pos != 0)
    fp.setField(pos->field);
  
  ((const NumberFormat*)fmt)->format(number, res, fp);
  
  if(pos != 0) {
    pos->beginIndex = fp.getBeginIndex();
    pos->endIndex = fp.getEndIndex();
  }
  
  return res.extract(result, resultLength, *status);
}

U_CAPI int32_t U_EXPORT2 
unum_formatDoubleCurrency(const UNumberFormat* fmt,
                          double number,
                          UChar* currency,
                          UChar* result,
                          int32_t resultLength,
                          UFieldPosition* pos, /* ignored if 0 */
                          UErrorCode* status) {
    if (U_FAILURE(*status)) return -1;

    UnicodeString res;
    if (!(result==NULL && resultLength==0)) {
        // NULL destination for pure preflighting: empty dummy string
        // otherwise, alias the destination buffer
        res.setTo(result, 0, resultLength);
    }
    
    FieldPosition fp;
    if (pos != 0) {
        fp.setField(pos->field);
    }
    CurrencyAmount *tempCurrAmnt = new CurrencyAmount(number, currency, *status);
    // Check for null pointer.
    if (tempCurrAmnt == NULL) {
        *status = U_MEMORY_ALLOCATION_ERROR;
        return -1;
    }
    Formattable n(tempCurrAmnt);
    ((const NumberFormat*)fmt)->format(n, res, fp, *status);
    
    if (pos != 0) {
        pos->beginIndex = fp.getBeginIndex();
        pos->endIndex = fp.getEndIndex();
    }
  
    return res.extract(result, resultLength, *status);
}

static void
parseRes(Formattable& res,
         const   UNumberFormat*  fmt,
         const   UChar*          text,
         int32_t         textLength,
         int32_t         *parsePos /* 0 = start */,
         UBool parseCurrency,
         UErrorCode      *status)
{
    if(U_FAILURE(*status))
        return;
    
    int32_t len = (textLength == -1 ? u_strlen(text) : textLength);
    const UnicodeString src((UChar*)text, len, len);
    ParsePosition pp;
    
    if(parsePos != 0)
        pp.setIndex(*parsePos);
    
    if (parseCurrency) {
        ((const NumberFormat*)fmt)->parseCurrency(src, res, pp);
    } else {
        ((const NumberFormat*)fmt)->parse(src, res, pp);
    }
    
    if(parsePos != 0) {
        if(pp.getErrorIndex() == -1)
            *parsePos = pp.getIndex();
        else {
            *parsePos = pp.getErrorIndex();
            *status = U_PARSE_ERROR;
        }
    }
}

U_CAPI int32_t U_EXPORT2
unum_parse(    const   UNumberFormat*  fmt,
        const   UChar*          text,
        int32_t         textLength,
        int32_t         *parsePos /* 0 = start */,
        UErrorCode      *status)
{
    Formattable res;
    parseRes(res, fmt, text, textLength, parsePos, FALSE, status);
    return res.getLong(*status);
}

U_CAPI int64_t U_EXPORT2
unum_parseInt64(    const   UNumberFormat*  fmt,
        const   UChar*          text,
        int32_t         textLength,
        int32_t         *parsePos /* 0 = start */,
        UErrorCode      *status)
{
    Formattable res;
    parseRes(res, fmt, text, textLength, parsePos, FALSE, status);
    return res.getInt64(*status);
}

U_CAPI double U_EXPORT2
unum_parseDouble(    const   UNumberFormat*  fmt,
            const   UChar*          text,
            int32_t         textLength,
            int32_t         *parsePos /* 0 = start */,
            UErrorCode      *status)
{
    Formattable res;
    parseRes(res, fmt, text, textLength, parsePos, FALSE, status);
    return res.getDouble(*status);
}

U_CAPI double U_EXPORT2
unum_parseDoubleCurrency(const UNumberFormat* fmt,
                         const UChar* text,
                         int32_t textLength,
                         int32_t* parsePos, /* 0 = start */
                         UChar* currency,
                         UErrorCode* status) {
    Formattable res;
    parseRes(res, fmt, text, textLength, parsePos, TRUE, status);
    currency[0] = 0;
    if (res.getType() == Formattable::kObject &&
        res.getObject()->getDynamicClassID() == CurrencyAmount::getStaticClassID()) {
        const CurrencyAmount* c = (const CurrencyAmount*) res.getObject();
        u_strcpy(currency, c->getISOCurrency());
    }
    return res.getDouble(*status);
}

U_CAPI const char* U_EXPORT2
unum_getAvailable(int32_t index)
{
    return uloc_getAvailable(index);
}

U_CAPI int32_t U_EXPORT2
unum_countAvailable()
{
    return uloc_countAvailable();
}

U_CAPI int32_t U_EXPORT2
unum_getAttribute(const UNumberFormat*          fmt,
          UNumberFormatAttribute  attr)
{
  if (((const NumberFormat*)fmt)->getDynamicClassID() == DecimalFormat::getStaticClassID()) {
    const DecimalFormat* df = (const DecimalFormat*) fmt;
    switch(attr) {
    case UNUM_PARSE_INT_ONLY:
        return df->isParseIntegerOnly();
        
    case UNUM_GROUPING_USED:
        return df->isGroupingUsed();
        
    case UNUM_DECIMAL_ALWAYS_SHOWN:
        return df->isDecimalSeparatorAlwaysShown();    
        
    case UNUM_MAX_INTEGER_DIGITS:
        return df->getMaximumIntegerDigits();
        
    case UNUM_MIN_INTEGER_DIGITS:
        return df->getMinimumIntegerDigits();
        
    case UNUM_INTEGER_DIGITS:
        // TBD: what should this return?
        return df->getMinimumIntegerDigits();
        
    case UNUM_MAX_FRACTION_DIGITS:
        return df->getMaximumFractionDigits();
        
    case UNUM_MIN_FRACTION_DIGITS:
        return df->getMinimumFractionDigits();
        
    case UNUM_FRACTION_DIGITS:
        // TBD: what should this return?
        return df->getMinimumFractionDigits();
        
    case UNUM_SIGNIFICANT_DIGITS_USED:
        return df->areSignificantDigitsUsed();
        
    case UNUM_MAX_SIGNIFICANT_DIGITS:
        return df->getMaximumSignificantDigits();
        
    case UNUM_MIN_SIGNIFICANT_DIGITS:
        return df->getMinimumSignificantDigits();
        
    case UNUM_MULTIPLIER:
        return df->getMultiplier();    
        
    case UNUM_GROUPING_SIZE:
        return df->getGroupingSize();    
        
    case UNUM_ROUNDING_MODE:
        return df->getRoundingMode();
        
    case UNUM_FORMAT_WIDTH:
        return df->getFormatWidth();
        
    case UNUM_PADDING_POSITION:
        return df->getPadPosition();
        
    case UNUM_SECONDARY_GROUPING_SIZE:
        return df->getSecondaryGroupingSize();
        
    default:
        /* enums out of sync? unsupported enum? */
        break;
    }
  } else {
    U_ASSERT(((const NumberFormat*)fmt)->getDynamicClassID() == RuleBasedNumberFormat::getStaticClassID());
    if (attr == UNUM_LENIENT_PARSE) {
#if !UCONFIG_NO_COLLATION
      return ((const RuleBasedNumberFormat*)fmt)->isLenient();
#endif
    }
  }

  return -1;
}

U_CAPI void U_EXPORT2
unum_setAttribute(    UNumberFormat*          fmt,
            UNumberFormatAttribute  attr,
            int32_t                 newValue)
{
  if (((NumberFormat*)fmt)->getDynamicClassID() == DecimalFormat::getStaticClassID()) {
    DecimalFormat* df = (DecimalFormat*) fmt;
    switch(attr) {
    case UNUM_PARSE_INT_ONLY:
        df->setParseIntegerOnly(newValue!=0);
        break;
        
    case UNUM_GROUPING_USED:
        df->setGroupingUsed(newValue!=0);
        break;
        
    case UNUM_DECIMAL_ALWAYS_SHOWN:
        df->setDecimalSeparatorAlwaysShown(newValue!=0);
        break;
        
    case UNUM_MAX_INTEGER_DIGITS:
        df->setMaximumIntegerDigits(newValue);
        break;
        
    case UNUM_MIN_INTEGER_DIGITS:
        df->setMinimumIntegerDigits(newValue);
        break;
        
    case UNUM_INTEGER_DIGITS:
        df->setMinimumIntegerDigits(newValue);
        df->setMaximumIntegerDigits(newValue);
        break;
        
    case UNUM_MAX_FRACTION_DIGITS:
        df->setMaximumFractionDigits(newValue);
        break;
        
    case UNUM_MIN_FRACTION_DIGITS:
        df->setMinimumFractionDigits(newValue);
        break;
        
    case UNUM_FRACTION_DIGITS:
        df->setMinimumFractionDigits(newValue);
        df->setMaximumFractionDigits(newValue);
        break;
        
    case UNUM_SIGNIFICANT_DIGITS_USED:
        df->setSignificantDigitsUsed(newValue!=0);
        break;

    case UNUM_MAX_SIGNIFICANT_DIGITS:
        df->setMaximumSignificantDigits(newValue);
        break;
        
    case UNUM_MIN_SIGNIFICANT_DIGITS:
        df->setMinimumSignificantDigits(newValue);
        break;
        
    case UNUM_MULTIPLIER:
        df->setMultiplier(newValue);    
        break;
        
    case UNUM_GROUPING_SIZE:
        df->setGroupingSize(newValue);    
        break;
        
    case UNUM_ROUNDING_MODE:
        df->setRoundingMode((DecimalFormat::ERoundingMode)newValue);
        break;
        
    case UNUM_FORMAT_WIDTH:
        df->setFormatWidth(newValue);
        break;
        
    case UNUM_PADDING_POSITION:
        /** The position at which padding will take place. */
        df->setPadPosition((DecimalFormat::EPadPosition)newValue);
        break;
        
    case UNUM_SECONDARY_GROUPING_SIZE:
        df->setSecondaryGroupingSize(newValue);
        break;
        
    default:
        /* Shouldn't get here anyway */
        break;
    }
  } else {
    U_ASSERT(((NumberFormat*)fmt)->getDynamicClassID() == RuleBasedNumberFormat::getStaticClassID());
    if (attr == UNUM_LENIENT_PARSE) {
#if !UCONFIG_NO_COLLATION
      ((RuleBasedNumberFormat*)fmt)->setLenient((UBool)newValue);
#endif
    }
  }
}

U_CAPI double U_EXPORT2
unum_getDoubleAttribute(const UNumberFormat*          fmt,
          UNumberFormatAttribute  attr)
{
    if (((const NumberFormat*)fmt)->getDynamicClassID() == DecimalFormat::getStaticClassID() && 
    attr == UNUM_ROUNDING_INCREMENT) {
        return ((const DecimalFormat*)fmt)->getRoundingIncrement();
    } else {
        return -1.0;
    }
}

U_CAPI void U_EXPORT2
unum_setDoubleAttribute(    UNumberFormat*          fmt,
            UNumberFormatAttribute  attr,
            double                 newValue)
{
    if (((NumberFormat*)fmt)->getDynamicClassID() == DecimalFormat::getStaticClassID() && 
    attr == UNUM_ROUNDING_INCREMENT) {   
        ((DecimalFormat*)fmt)->setRoundingIncrement(newValue);
    }
}

U_CAPI int32_t U_EXPORT2
unum_getTextAttribute(const UNumberFormat*  fmt,
            UNumberFormatTextAttribute      tag,
            UChar*                          result,
            int32_t                         resultLength,
            UErrorCode*                     status)
{
    if(U_FAILURE(*status))
        return -1;

    UnicodeString res;
    if(!(result==NULL && resultLength==0)) {
        // NULL destination for pure preflighting: empty dummy string
        // otherwise, alias the destination buffer
        res.setTo(result, 0, resultLength);
    }

    if (((const NumberFormat*)fmt)->getDynamicClassID() == DecimalFormat::getStaticClassID()) {
        const DecimalFormat* df = (const DecimalFormat*) fmt;
        switch(tag) {
        case UNUM_POSITIVE_PREFIX:
            df->getPositivePrefix(res);
            break;

        case UNUM_POSITIVE_SUFFIX:
            df->getPositiveSuffix(res);
            break;

        case UNUM_NEGATIVE_PREFIX:
            df->getNegativePrefix(res);
            break;

        case UNUM_NEGATIVE_SUFFIX:
            df->getNegativeSuffix(res);
            break;

        case UNUM_PADDING_CHARACTER:
            res = df->getPadCharacterString();
            break;

        case UNUM_CURRENCY_CODE:
            res = UnicodeString(df->getCurrency());
            break;

        default:
            *status = U_UNSUPPORTED_ERROR;
            return -1;
        }
    } else {
        U_ASSERT(((const NumberFormat*)fmt)->getDynamicClassID() == RuleBasedNumberFormat::getStaticClassID());
        const RuleBasedNumberFormat* rbnf = (const RuleBasedNumberFormat*)fmt;
        if (tag == UNUM_DEFAULT_RULESET) {
            res = rbnf->getDefaultRuleSetName();
        } else if (tag == UNUM_PUBLIC_RULESETS) {
            int32_t count = rbnf->getNumberOfRuleSetNames();
            for (int i = 0; i < count; ++i) {
                res += rbnf->getRuleSetName(i);
                res += (UChar)0x003b; // semicolon
            }
        } else {
            *status = U_UNSUPPORTED_ERROR;
            return -1;
        }
    }

    return res.extract(result, resultLength, *status);
}

U_CAPI void U_EXPORT2
unum_setTextAttribute(    UNumberFormat*                    fmt,
            UNumberFormatTextAttribute      tag,
            const    UChar*                            newValue,
            int32_t                            newValueLength,
            UErrorCode                        *status)
{
    if(U_FAILURE(*status))
        return;
    
    int32_t len = (newValueLength == -1 ? u_strlen(newValue) : newValueLength);
    const UnicodeString val((UChar*)newValue, len, len);
    
    if (((NumberFormat*)fmt)->getDynamicClassID() == DecimalFormat::getStaticClassID()) {
      DecimalFormat* df = (DecimalFormat*) fmt;
      switch(tag) {
      case UNUM_POSITIVE_PREFIX:
        df->setPositivePrefix(val);
        break;
        
      case UNUM_POSITIVE_SUFFIX:
        df->setPositiveSuffix(val);
        break;
        
      case UNUM_NEGATIVE_PREFIX:
        df->setNegativePrefix(val);
        break;
        
      case UNUM_NEGATIVE_SUFFIX:
        df->setNegativeSuffix(val);
        break;
        
      case UNUM_PADDING_CHARACTER:
        df->setPadCharacter(*newValue);
        break;
        
      case UNUM_CURRENCY_CODE:
        df->setCurrency(newValue, *status);
        break;
        
      default:
        *status = U_UNSUPPORTED_ERROR;
        break;
      }
    } else {
      U_ASSERT(((NumberFormat*)fmt)->getDynamicClassID() == RuleBasedNumberFormat::getStaticClassID());
      if (tag == UNUM_DEFAULT_RULESET) {
    ((RuleBasedNumberFormat*)fmt)->setDefaultRuleSet(newValue, *status);
      } else {
    *status = U_UNSUPPORTED_ERROR;
      }
    }
}

U_CAPI int32_t U_EXPORT2
unum_toPattern(    const    UNumberFormat*          fmt,
        UBool                  isPatternLocalized,
        UChar*                  result,
        int32_t                 resultLength,
        UErrorCode*             status)
{
    if(U_FAILURE(*status))
        return -1;
    
    UnicodeString pat;
    if(!(result==NULL && resultLength==0)) {
        // NULL destination for pure preflighting: empty dummy string
        // otherwise, alias the destination buffer
        pat.setTo(result, 0, resultLength);
    }

    if (((const NumberFormat*)fmt)->getDynamicClassID() == DecimalFormat::getStaticClassID()) {
      const DecimalFormat* df = (const DecimalFormat*) fmt;
      if(isPatternLocalized)
        df->toLocalizedPattern(pat);
      else
        df->toPattern(pat);
    } else {
      U_ASSERT(((const NumberFormat*)fmt)->getDynamicClassID() == RuleBasedNumberFormat::getStaticClassID());
      pat = ((const RuleBasedNumberFormat*)fmt)->getRules();
    }
    return pat.extract(result, resultLength, *status);
}

U_CAPI int32_t U_EXPORT2
unum_getSymbol(const UNumberFormat *fmt,
               UNumberFormatSymbol symbol,
               UChar *buffer,
               int32_t size,
               UErrorCode *status)
{
    if(status==NULL || U_FAILURE(*status)) {
        return 0;
    }
    
    if(fmt==NULL || (uint16_t)symbol>=UNUM_FORMAT_SYMBOL_COUNT) {
        *status=U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    if (((const NumberFormat*)fmt)->getDynamicClassID() != DecimalFormat::getStaticClassID()) {
      *status = U_UNSUPPORTED_ERROR;
      return 0;
    }

    return ((const DecimalFormat *)fmt)->
      getDecimalFormatSymbols()->
        getConstSymbol((DecimalFormatSymbols::ENumberFormatSymbol)symbol).
          extract(buffer, size, *status);
}

U_CAPI void U_EXPORT2
unum_setSymbol(UNumberFormat *fmt,
               UNumberFormatSymbol symbol,
               const UChar *value,
               int32_t length,
               UErrorCode *status)
{
    if(status==NULL || U_FAILURE(*status)) {
        return;
    }
    
    if(fmt==NULL || (uint16_t)symbol>=UNUM_FORMAT_SYMBOL_COUNT || value==NULL || length<-1) {
        *status=U_ILLEGAL_ARGUMENT_ERROR;
        return;
    }
    
    if (((NumberFormat*)fmt)->getDynamicClassID() != DecimalFormat::getStaticClassID()) {
      *status = U_UNSUPPORTED_ERROR;
      return;
    }

    DecimalFormatSymbols symbols(*((DecimalFormat *)fmt)->getDecimalFormatSymbols());
    symbols.setSymbol((DecimalFormatSymbols::ENumberFormatSymbol)symbol,
        UnicodeString(value, length));  /* UnicodeString can handle the case when length = -1. */
    ((DecimalFormat *)fmt)->setDecimalFormatSymbols(symbols);
}

U_CAPI void U_EXPORT2
unum_applyPattern(  UNumberFormat  *format,
                    UBool          localized,
                    const UChar    *pattern,
                    int32_t        patternLength,
                    UParseError    *parseError,
                    UErrorCode*    status)
{
    UErrorCode tStatus = U_ZERO_ERROR;
    UParseError tParseError;
    
    if(parseError == NULL){
        parseError = &tParseError;
    }
    
    if(status==NULL){
        status = &tStatus;
    }
    
    int32_t len = (patternLength == -1 ? u_strlen(pattern) : patternLength);
    const UnicodeString pat((UChar*)pattern, len, len);
    
    // Verify if the object passed is a DecimalFormat object
    if (((NumberFormat*)format)->getDynamicClassID() == DecimalFormat::getStaticClassID()) {
      if(localized) {
        ((DecimalFormat*)format)->applyLocalizedPattern(pat,*parseError, *status);
      } else {
        ((DecimalFormat*)format)->applyPattern(pat,*parseError, *status);
      }
    } else {
      *status = U_UNSUPPORTED_ERROR;
      return;
    }
}

U_CAPI const char* U_EXPORT2
unum_getLocaleByType(const UNumberFormat *fmt,
                     ULocDataLocaleType type,
                     UErrorCode* status)
{
    if (fmt == NULL) {
        if (U_SUCCESS(*status)) {
            *status = U_ILLEGAL_ARGUMENT_ERROR;
        }
        return NULL;
    }
    return ((const Format*)fmt)->getLocaleID(type, *status);
}

#endif /* #if !UCONFIG_NO_FORMATTING */
